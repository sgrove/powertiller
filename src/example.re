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
    "title": string,
  },
};

type searchNode = {
  .
  "id": string,
  "snippet": {
    .
    "description": string,
    "title": string,
  },
};

type action =
  | Click
  | Toggle
  | SelectSearchNode(searchNode);

type state = {
  count: int,
  show: bool,
  selectedVideo: option(video),
};

let component = ReasonReact.reducerComponent("VideoSelector");

module Query = ReasonApollo.CreateQuery(FindPotentialVideosQuery);

let make = (~term, ~presentationId, _children) => {
  ...component,
  initialState: () => {count: 0, show: false, selectedVideo: None},
  reducer: (action, state) =>
    switch (action) {
    | Click => ReasonReact.Update({...state, count: state.count + 1})
    | Toggle => ReasonReact.Update({...state, show: ! state.show})
    | SelectSearchNode(searchNode) =>
      ReasonReact.Update({...state, selectedVideo: Some(searchNode)})
    },
  render: self => {
    open ReasonReact;
    Js.log2("term", term);
    let videosQuery = FindPotentialVideosQuery.make(~q=term, ());
    Js.log2("FPVQ", videosQuery);
    <Query variables=videosQuery##variables>
      ...(
           ({result}) =>
             switch (result) {
             | Loading => <div> (string("Loading")) </div>
             | Error(error) =>
               <div>
                 (
                   string(
                     Option.default(
                       "Some error",
                       Js.Json.stringifyAny(error),
                     ),
                   )
                 )
               </div>
             | Data(result) =>
               <div>
                 <pre>
                   (
                     string(
                       Option.default(
                         "Baffled....",
                         Js.Json.stringifyAny(result),
                       ),
                     )
                   )
                 </pre>
                 <ul>
                   (
                     ReasonReact.array(
                       switch (result##youTubeSearch) {
                       | None => [|string("No search results")|]
                       | Some(search) =>
                         Array.map(
                           edge =>
                             <li
                               onClick=(
                                 _ => self.send(SelectSearchNode(edge##node))
                               )>
                               (
                                 string(
                                   edge##node##snippet##title
                                   ++ " - "
                                   ++ edge##node##snippet##description,
                                 )
                               )
                               (
                                 switch (self.state.selectedVideo) {
                                 | None => ReasonReact.null
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
                                     ReasonReact.null;
                                   }
                                 }
                               )
                             </li>,
                           search##items##edges,
                         )
                       },
                     )
                   )
                 </ul>
               </div>
             }
         )
    </Query>;
  },
};
