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

let mutationComponent = ReasonReact.statelessComponent("VideoSetter");

module Mutation = Client.Instance.Mutation;

let make = (~presentationId, ~videoId, _children) => {
  ...mutationComponent,
  render: _self =>
    <Mutation>
      ...(
           (mutate /* Mutation to call */, result /* Result of your mutation */) =>
             switch result {
             | NotCalled =>
               <div>
                 <button
                   onClick=(
                     _mouseEvent => {
                       let setVideoMutation =
                         SetPresentationVideoIdMutation.make(
                           ~presentationId,
                           ~youTubeVideoId=videoId,
                           ()
                         );
                       mutate(setVideoMutation);
                     }
                   )>
                   (Utils.s("Set this video"))
                 </button>
               </div>
             | Loading => <div> (Utils.s("Loading mutation result")) </div>
             | Loaded(response) =>
               <div>
                 (
                   Utils.s(
                     Utils.default(
                       "Couldn't get result",
                       Js.Json.stringifyAny(response)
                     )
                   )
                 )
               </div>
             | Failed(error) => <div> (Utils.s(error)) </div>
             }
         )
    </Mutation>
};
