open Utils;

let default = (value, option) =>
  switch option {
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
  "video_url": option(string)
};

type action =
  | Click
  | Toggle
  | SelectPresentation(presentation);

type state = {
  count: int,
  show: bool,
  selectedPresentation: option(presentation)
};

let component = ReasonReact.reducerComponent("Event");

module Query = Client.Instance.Query;

let make = (~eventId, _children) => {
  ...component,
  initialState: () => {count: 0, show: false, selectedPresentation: None},
  reducer: (action, state) =>
    switch action {
    | Click => ReasonReact.Update({...state, count: state.count + 1})
    | Toggle => ReasonReact.Update({...state, show: ! state.show})
    | SelectPresentation(presentation) =>
      ReasonReact.Update({...state, selectedPresentation: Some(presentation)})
    },
  render: self => {
    let videosQuery = FindEventPresentationsQuery.make(~id=eventId, ());
    <Query query=videosQuery>
      ...(
           (response, parse) =>
             switch response {
             | Loading => <div> (Utils.s("Loading")) </div>
             | Failed(error) => <div> (Utils.s(error)) </div>
             | Loaded(rawResult) =>
               let result = parse(rawResult);
               switch result##eventil {
               | None => s("No eventil")
               | Some(eventil) =>
                 switch eventil##event {
                 | None => s("No event")
                 | Some(event) =>
                   <div>
                     <ul>
                       (
                         ReasonReact.arrayToElement(
                           Array.map(
                             presentation => {
                               let names =
                                 Array.map(
                                   speaker => default("", speaker##name),
                                   presentation##speakers
                                 )
                                 |> Array.to_list
                                 |> String.concat(" ");
                               <li
                                 onClick=(
                                   (_) =>
                                     self.send(
                                       SelectPresentation(presentation)
                                     )
                                 )>
                                 (
                                   s(
                                     (
                                       switch presentation##video_url {
                                       | None => "X"
                                       | Some(_) => "Y"
                                       }
                                     )
                                     ++ " "
                                     ++ names
                                     ++ " : "
                                     ++ default(
                                          "No title",
                                          presentation##draft##title
                                        )
                                   )
                                 )
                               </li>;
                             },
                             event##presentations
                           )
                         )
                       )
                     </ul>
                     <hr />
                     (
                       switch self.state.selectedPresentation {
                       | None => ReasonReact.nullElement
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
               };
             }
         )
    </Query>;
  }
};
