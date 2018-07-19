open Utils;
open Option;
open ReasonReact;

let default = (value, option) =>
  switch (option) {
  | None => value
  | Some(value) => value
  };

let presentationToQueryTerm = presentation => {
  let names =
    Array.map(speaker => default("", speaker##name), presentation##speakers)
    |> Array.to_list
    |> String.concat(" ");
  names ++ " : " ++ default("No title", presentation##draft##title);
};

module FindEventPresentationsQuery = [%graphql
  {|
query findEventPresentations($id: String!) {
  eventil {
    event(id: $id) {
      id
      presentations {
        id
        draft {
          title
        }
        speakers {
          name
        }
        video_url
      }
    }
  }
}
|}
];

type presentation = {
  .
  "draft": {. "title": option(string)},
  "id": option(string),
  "speakers": Js.Array.t({. "name": option(string)}),
  "video_url": option(string),
};

type action =
  | Click
  | Toggle
  | SelectPresentation(presentation);

type state = {
  count: int,
  show: bool,
  selectedPresentation: option(presentation),
};

let component = ReasonReact.reducerComponent("Event");

module Query = ReasonApollo.CreateQuery(FindEventPresentationsQuery);

let make = (~eventId, _children) => {
  ...component,
  initialState: () => {count: 0, show: false, selectedPresentation: None},
  reducer: (action, state) =>
    switch (action) {
    | Click => ReasonReact.Update({...state, count: state.count + 1})
    | Toggle => ReasonReact.Update({...state, show: ! state.show})
    | SelectPresentation(presentation) =>
      ReasonReact.Update({
        ...state,
        selectedPresentation: Some(presentation),
      })
    },
  render: self => {
    let videosQuery = FindEventPresentationsQuery.make(~id=eventId, ());
    <Query variables=videosQuery##variables>
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
               switch (result##eventil) {
               | None => s("No eventil")
               | Some(eventil) =>
                 switch (eventil##event) {
                 | None => s("No event")
                 | Some(event) =>
                   <div>
                     <ul>
                       (
                         array(
                           Array.map(
                             presentation => {
                               let names =
                                 Array.map(
                                   speaker => default("", speaker##name),
                                   presentation##speakers,
                                 )
                                 |> Array.to_list
                                 |> String.concat(" ");
                               <li
                                 onClick=(
                                   _ =>
                                     self.send(
                                       SelectPresentation(presentation),
                                     )
                                 )>
                                 (
                                   s(
                                     (
                                       switch (presentation##video_url) {
                                       | None => "X"
                                       | Some(_) => "Y"
                                       }
                                     )
                                     ++ " "
                                     ++ names
                                     ++ " : "
                                     ++ default(
                                          "No title",
                                          presentation##draft##title,
                                        ),
                                   )
                                 )
                               </li>;
                             },
                             event##presentations,
                           ),
                         )
                       )
                     </ul>
                     <hr />
                     (
                       switch (self.state.selectedPresentation) {
                       | None => null
                       | Some(presentation) =>
                         let term = presentationToQueryTerm(presentation);
                         <Example
                           term
                           presentationId=(
                             Utils.getExn("presentationId", presentation##id)
                           )
                         />;
                       }
                     )
                   </div>
                 }
               }
             }
         )
    </Query>;
  },
};
