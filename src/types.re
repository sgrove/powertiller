type presentation = {
  .
  "draft": {. "title": option(string)},
  "id": option(string),
  "speakers": Js.Array.t({. "name": option(string)}),
  "video_url": option(string),
};

let presentationToQueryTerm = presentation => {
  open Option;
  let names =
    Array.map(speaker => default("", speaker##name), presentation##speakers)
    |> Array.to_list
    |> String.concat(" ");
  names ++ " : " ++ default("No title", presentation##draft##title);
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
