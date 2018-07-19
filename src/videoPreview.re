open Utils;

module RR = ReasonReact;

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
    let videoQuery = VideosDetailsQuery.make(~videoId, ());
    <Query variables=videoQuery##variables>
      ...(
           ({result}) =>
             switch (result) {
             | Loading => <div> (Utils.s("Loading")) </div>
             | Error(error) =>
               <div>
                 (
                   Utils.s(
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
                   | None => s("No video found for id " ++ videoId)
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
