module VideosDetailsQuery = [%graphql
  {|
query VideoDetailsQuery($videoId: String!) {
  youTubeVideo(id: $videoId) {
    id
    snippet {
      uploadChannel {
        snippet {
          publishedAtTs
          title
        }
      }
      description
    }
    player {
      embedHtml
    }
  }
}
|}
];

let component = ReasonReact.statelessComponent("VideoPreview");

module Query = ReasonApollo.CreateQuery(VideosDetailsQuery);

let make = (~videoId, _children) => {
  ...component,
  render: _self => {
    open ReasonReact;
    let videoQuery = VideosDetailsQuery.make(~videoId, ());
    <Query variables=videoQuery##variables>
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
                 (
                   switch (result##youTubeVideo) {
                   | None => string("No video found for id " ++ videoId)
                   | Some(video) =>
                     <div
                       dangerouslySetInnerHTML={
                         "__html":
                           switch (video##player) {
                           | None => "<strong>No video player available</strong>"
                           | Some(player) => player##embedHtml
                           },
                       }
                     />
                   }
                 )
               </div>
             }
         )
    </Query>;
  },
};
