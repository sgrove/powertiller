module Layout = Antd.Layout;
open Antd.Grid;

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

let make = (~term, ~presentation: Types.presentation, _children) => {
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
    let videosQuery = FindPotentialVideosQuery.make(~q=term, ());
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
                 <Layout>
                   <Layout.Header>
                     <h3 style=(ReactDOMRe.Style.make(~color="white", ()))>
                       (
                         presentation##draft##title
                         |> Option.expect("No title for presentation")
                         |> string
                       )
                       (string("  -  "))
                       <small>
                         (
                           string(
                             Types.presentationSpeakerNames(presentation),
                           )
                         )
                       </small>
                     </h3>
                   </Layout.Header>
                   <Layout>
                     <Layout.Sider
                       style=(
                         ReactDOMRe.Style.make(
                           ~color="hsla(0,0%,100%,.65)",
                           (),
                         )
                       )>
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
                                       _ =>
                                         self.send(
                                           SelectSearchNode(edge##node),
                                         )
                                     )>
                                     (
                                       string(
                                         edge##node##snippet##title
                                         ++ " - "
                                         ++ edge##node##snippet##description,
                                       )
                                     )
                                   </li>,
                                 search##items##edges,
                               )
                             },
                           )
                         )
                       </ul>
                     </Layout.Sider>
                     <Layout.Content>
                       (
                         switch (self.state.selectedVideo) {
                         | None => ReasonReact.null
                         | Some(selectedVideo) =>
                           <div>
                             <VideoPreview videoId=selectedVideo##id />
                             <VideoSetter
                               presentationId=(
                                 Option.expect(
                                   "No id for selected presentation in f34, ",
                                   presentation##id,
                                 )
                               )
                               videoId=selectedVideo##id
                             />
                           </div>
                         }
                       )
                     </Layout.Content>
                   </Layout>
                 </Layout>
               </div>
             }
         )
    </Query>;
  },
};
