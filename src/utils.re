let s = ReasonReact.stringToElement;

let default = (value, option) =>
  switch option {
  | None => value
  | Some(value) => value
  };

let getExn = (message, option) =>
  switch option {
  | None => raise(Failure(message))
  | Some(value) => value
  };
