module SetPresentationVideoIdMutation = [%graphql
  {|
mutation setEventilPresentationVideoId(
  $presentationId: String!
  $youTubeVideoId: String!
) {
  eventil {
    setVideoId(id: $presentationId, youtube_id: $youTubeVideoId) {
      draft {
        title
      }
    }
  }
}
|}
];

let mutationComponent = ReasonReact.statelessComponent("Video Setter");

module Mutation = ReasonApollo.CreateMutation(SetPresentationVideoIdMutation);

let make = (~presentationId, ~videoId, _children) => {
  ...mutationComponent,
  render: _self =>
    ReasonReact.(
      <Mutation>
        ...(
             (
               mutation /* Mutation to call */,
               {result} /* Result of your mutation */,
             ) =>
               switch (result) {
               | NotCalled =>
                 <div>
                   <Antd.Button
                     _type=`primary
                     onClick=(
                       _mouseEvent => {
                         let setVideoMutation =
                           SetPresentationVideoIdMutation.make(
                             ~presentationId,
                             ~youTubeVideoId=videoId,
                             (),
                           );
                         mutation(~variables=setVideoMutation##variables, ())
                         |> ignore;
                       }
                     )>
                     (string("Set this video"))
                   </Antd.Button>
                 </div>
               | Loading => <div> (string("Loading mutation result")) </div>
               | Data(response) =>
                 <div>
                   (
                     string(
                       Option.default(
                         "Couldn't get result",
                         Js.Json.stringifyAny(response),
                       ),
                     )
                   )
                 </div>
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
               }
           )
      </Mutation>
    ),
};
