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

module Query = Client.Instance.Query;

let make = (~videoId, _children) => {
  ...component,
  render: _self => {
    let videoQuery = VideosDetailsQuery.make(~videoId, ());
    <Query query=videoQuery>
      ...(
           (response, parse) =>
             switch response {
             | Loading => <div> (Utils.s("Loading")) </div>
             | Failed(error) => <div> (Utils.s(error)) </div>
             | Loaded(rawResult) =>
               let result = parse(rawResult);
               <div>
                 (
                   switch result##youTubeVideo {
                   | None => s("No video found for id " ++ videoId)
                   | Some(video) =>
                     <div
                       dangerouslySetInnerHTML={
                         "__html":
                           switch video##player {
                           | None => "<strong>No video player available</strong>"
                           | Some(player) => player##embedHtml
                           }
                       }
                     />
                   }
                 )
               </div>;
             }
         )
    </Query>;
  }
};
