open ReasonReact;

module FindEventPresentationsQuery = [%graphql
  {|
query findEventPresentations($id: String!) {
  eventil {
    event(id: $id) {
      id
      name
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

type action =
  | Click
  | Toggle;

type state = {
  count: int,
  show: bool,
};

let component = ReasonReact.reducerComponent("Event");

module Query = ReasonApollo.CreateQuery(FindEventPresentationsQuery);

let icon = kind => <Antd.Icon type_=kind />;

let make = (~eventId, ~onPresentationSelected, _children) => {
  ...component,
  initialState: () => {count: 0, show: false},
  reducer: (action, state) =>
    switch (action) {
    | Click => Update({...state, count: state.count + 1})
    | Toggle => Update({...state, show: ! state.show})
    },
  render: _self => {
    let videosQuery = FindEventPresentationsQuery.make(~id=eventId, ());
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
               switch (result##eventil) {
               | None => string("No eventil")
               | Some(eventil) =>
                 switch (eventil##event) {
                 | None => string("No event")
                 | Some(event) =>
                   <div>
                     <h2 style=(ReactDOMRe.Style.make(~color="white", ()))>
                       (
                         event##name
                         |> Option.default("Untitled Event")
                         |> string
                       )
                     </h2>
                     <Antd.Menu
                       mode=`Inline
                       multiple=false
                       onSelect=(
                         selectEvent => {
                           let presentationId = selectEvent##key;
                           let presentation =
                             event##presentations
                             |> Array.to_list
                             |> List.find(pres =>
                                  Option.expect(
                                    "Presentation had no id in amkn",
                                    pres##id,
                                  )
                                  == presentationId
                                );
                           onPresentationSelected(presentation);
                         }
                       )>
                       (
                         event##presentations
                         |> Array.mapi((idx, presentation) => {
                              let _names =
                                presentation##speakers
                                |> Array.to_list
                                |> List.filter(speaker =>
                                     switch (speaker##name) {
                                     | None => false
                                     | Some(_) => true
                                     }
                                   )
                                |> List.map(speaker =>
                                     Option.default("", speaker##name)
                                   )
                                |> String.concat(", ");
                              <Antd.Menu.Item
                                id=(
                                  Option.default(
                                    string_of_int(idx),
                                    presentation##id,
                                  )
                                )
                                key=(
                                  Option.expect(
                                    "Selected presentation had no id",
                                    presentation##id,
                                  )
                                )>
                                    <div>
                                      (
                                        switch (presentation##video_url) {
                                        | None => icon(Antd.IconName.warning)
                                        | Some(_) =>
                                          icon(Antd.IconName.checkSquare)
                                        }
                                      )
                                      (
                                        switch (presentation##draft) {
                                        | None => null
                                        | Some(draft) =>
                                          draft##title
                                          |> Option.default("Untitled")
                                          |> string
                                        }
                                      )
                                    </div>
                                  </Antd.Menu.Item> /* ) */;
                              /*   _ => onPresentationSelected(presentation) */
                              /* onSelect=( */
                            })
                         |> array
                       )
                     </Antd.Menu>
                   </div>
                 }
               }
             }
         )
    </Query>;
  },
};
