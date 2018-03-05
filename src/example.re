open Utils;

module RR = ReasonReact;

let default = (value, option) =>
  switch option {
  | None => value
  | Some(value) => value
  };

module FindPotentialVideosQuery = [%graphql
  {|
query findPotentialVideos($q: String!) {
  youTubeSearch(q: $q, maxResults: 10) {
    items {
      edges {
        node {
          id
          snippet {
            title
            description
          }
        }
      }
    }
  }
}
|}
];

type video = {
  .
  "id": string,
  "snippet": {
    .
    "description": string,
    "title": string
  }
};

type searchNode = {
  .
  "id": string,
  "snippet": {
    .
    "description": string,
    "title": string
  }
};

type action =
  | Click
  | Toggle
  | SelectSearchNode(searchNode);

type state = {
  count: int,
  show: bool,
  selectedVideo: option(video)
};

let component = ReasonReact.reducerComponent("VideoSelector");

module Query = Client.Instance.Query;

let make = (~term, ~presentationId, _children) => {
  ...component,
  initialState: () => {count: 0, show: false, selectedVideo: None},
  reducer: (action, state) =>
    switch action {
    | Click => ReasonReact.Update({...state, count: state.count + 1})
    | Toggle => ReasonReact.Update({...state, show: ! state.show})
    | SelectSearchNode(searchNode) =>
      ReasonReact.Update({...state, selectedVideo: Some(searchNode)})
    },
  render: self => {
    Js.log2("term", term);
    let videosQuery = FindPotentialVideosQuery.make(~q=term, ());
    Js.log2("FPVQ", videosQuery);
    <Query query=videosQuery>
      ...(
           (response, parse) =>
             switch response {
             | Loading => <div> (Utils.s("Loading")) </div>
             | Failed(error) => <div> (Utils.s(error)) </div>
             | Loaded(rawResult) =>
               let result = parse(rawResult);
               <div>
                 <pre>
                   (s(default("Baffled....", Js.Json.stringifyAny(rawResult))))
                 </pre>
                 <ul>
                   (
                     ReasonReact.arrayToElement(
                       switch result##youTubeSearch {
                       | None => [|s("No search results")|]
                       | Some(search) =>
                         Array.map(
                           edge =>
                             <li
                               onClick=(
                                 (_) => self.send(SelectSearchNode(edge##node))
                               )>
                               (
                                 s(
                                   edge##node##snippet##title
                                   ++ " - "
                                   ++ edge##node##snippet##description
                                 )
                               )
                               (
                                 switch self.state.selectedVideo {
                                 | None => ReasonReact.nullElement
                                 | Some(selectedVideo) =>
                                   if (selectedVideo##id == edge##node##id) {
                                     <div>
                                       <VideoSetter
                                         presentationId
                                         videoId=selectedVideo##id
                                       />
                                       <VideoPreview
                                         videoId=selectedVideo##id
                                       />
                                     </div>;
                                   } else {
                                     ReasonReact.nullElement;
                                   }
                                 }
                               )
                             </li>,
                           search##items##edges
                         )
                       }
                     )
                   )
                 </ul>
               </div>;
             }
         )
    </Query>;
  }
};
