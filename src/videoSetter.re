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
    <Mutation>
      ...(
           (
             mutation /* Mutation to call */,
             {result} /* Result of your mutation */,
           ) =>
             switch (result) {
             | NotCalled =>
               <div>
                 <button
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
                   (Utils.s("Set this video"))
                 </button>
               </div>
             | Loading => <div> (Utils.s("Loading mutation result")) </div>
             | Data(response) =>
               <div>
                 (
                   Utils.s(
                     Utils.default(
                       "Couldn't get result",
                       Js.Json.stringifyAny(response),
                     ),
                   )
                 )
               </div>
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
             }
         )
    </Mutation>,
};
