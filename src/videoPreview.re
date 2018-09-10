module VideosDetailsQuery = [%graphql
  {|
query VideoWithCaptionsQuery($videoId: String!) {
  youTube {
    video(id: $videoId) {
     id
     snippet {
       title
       publishedAt
       description
       channelTitle
     }
     player {
       embedHtml
     }
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
                   switch (result##youTube##video) {
                   | None => string("No video found for id " ++ videoId)
                   | Some(video) =>
                     <div>
                       <div
                         dangerouslySetInnerHTML={
                           "__html":
                             switch (video##player) {
                             | None => "<strong>No video player available</strong>"
                             | Some(player) =>
                               switch (player##embedHtml) {
                               | None => "<strong>No video embed html available</strong>"
                               | Some(html) => html
                               }
                             },
                         }
                       />
                       (
                         switch (video##snippet) {
                         | None => string("No video metadata available")
                         | Some(snippet) =>
                           <div>
                             <p>
                               (
                                 string(
                                   snippet##publishedAt
                                   |> Option.default(
                                        "No published date available",
                                      ),
                                 )
                               )
                               (
                                 string(
                                   "  ("
                                   ++ (
                                     snippet##channelTitle
                                     |> Option.default(
                                          "No channel title available",
                                        )
                                   )
                                   ++ ")  ",
                                 )
                               )
                             </p>
                             <p>
                               (
                                 string(
                                   snippet##description
                                   |> Option.default(
                                        "No description available",
                                      ),
                                 )
                               )
                             </p>
                           </div>
                         }
                       )
                     </div>
                   }
                 )
               </div>
             }
         )
    </Query>;
  },
};
