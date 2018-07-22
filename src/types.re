type presentation = {
  .
  "draft": option({. "title": option(string)}),
  "id": option(string),
  "speakers": Js.Array.t({. "name": option(string)}),
  "video_url": option(string),
};

let presentationTitle = presentation =>
  switch (presentation##draft) {
  | None => None
  | Some(draft) => draft##title
  };

let presentationToQueryTerm = presentation => {
  open Option;
  let names =
    Array.map(speaker => default("", speaker##name), presentation##speakers)
    |> Array.to_list
    |> String.concat(" ");
  names ++ " : " ++ default("No title", presentationTitle(presentation));
};

let presentationSpeakerNames = presentation =>
  presentation##speakers
  |> Array.to_list
  |> List.filter(speaker =>
       switch (speaker##name) {
       | None => false
       | Some(_) => true
       }
     )
  |> List.map(speaker => Option.expect("Speaker had no name", speaker##name))
  |> String.concat(", ");
