type action =
  | SetEventId(string)
  | SetVideoId(string)
  | SetUrl(option(string))
  | SetEventilLoggedIn(bool)
  | SetGithubLoggedIn(bool)
  | SetGoogleLoggedIn(bool)
  | SetTwitterLoggedIn(bool)
  | Fail;

type state = {
  oneAuth: Js.t({.}),
  videoId: option(string),
  currentUrl: option(string),
  failed: bool,
  eventId: string,
  isEventilLoggedIn: bool,
  isGithubLoggedIn: bool,
  isYouTubeLoggedIn: bool,
  isTwitterLoggedIn: bool,
};

let component = ReasonReact.reducerComponent("Page");

let make = (~forcedVideoId=?, _children) => {
  ...component,
  initialState: () => {
    eventId: "nordic-js-2017",
    oneAuth: Client.auth,
    videoId: None,
    failed: false,
    currentUrl: None,
    isEventilLoggedIn: false,
    isGithubLoggedIn: false,
    isYouTubeLoggedIn: false,
    isTwitterLoggedIn: false,
  },
  reducer: (action, state) =>
    switch (action) {
    | SetVideoId(videoId) =>
      ReasonReact.Update({...state, videoId: Some(videoId)})
    | SetEventId(eventId) => ReasonReact.Update({...state, eventId})
    | SetUrl(url) =>
      switch (url) {
      | None => ReasonReact.Update({...state, currentUrl: None})
      | Some(url) =>
        let videoId: option(string) =
          switch (Js.String.match([%bs.re "/v=([a-zA-Z0-9-_]+)/"], url)) {
          | None => None
          | Some(matches) => Some(matches[1])
          };
        ReasonReact.Update({...state, currentUrl: Some(url), videoId});
      }
    | SetEventilLoggedIn(isLoggedIn) =>
      ReasonReact.Update({...state, isEventilLoggedIn: isLoggedIn})
    | SetGithubLoggedIn(isLoggedIn) =>
      ReasonReact.Update({...state, isGithubLoggedIn: isLoggedIn})
    | SetGoogleLoggedIn(isLoggedIn) =>
      ReasonReact.Update({...state, isYouTubeLoggedIn: isLoggedIn})
    | SetTwitterLoggedIn(isLoggedIn) =>
      ReasonReact.Update({...state, isTwitterLoggedIn: isLoggedIn})
    | Fail => ReasonReact.Update({...state, failed: true})
    },
  didMount: self => {
    try (
      Chrome.Tabs.getActive(activeTab => {
        Js.log2("Active tab:", activeTab);
        self.send(SetUrl(Js.Nullable.toOption(activeTab##url)));
      })
    ) {
    | _ =>
      switch (forcedVideoId) {
      | None => ()
      | Some(videoId) => self.send(SetVideoId(videoId))
      }
    };
    OneGraphAuth.isLoggedIn(self.state.oneAuth, "youtube")
    |> Js.Promise.then_((isLoggedIn: bool) => {
         Js.log2("User is logged in to YouTube: ", isLoggedIn);
         self.send(SetGoogleLoggedIn(isLoggedIn));
         switch (isLoggedIn) {
         | false =>
           Js.log("Forcing YouTube login");
           OneGraphAuth.login(self.state.oneAuth, "youtube")
           |> Js.Promise.then_(() =>
                OneGraphAuth.isLoggedIn(self.state.oneAuth, "youtube")
                |> Js.Promise.then_(isLoggedIn => {
                     Js.log2(
                       "User is logged in to YouTube after login: ",
                       isLoggedIn,
                     );
                     self.send(SetGoogleLoggedIn(isLoggedIn));
                     Js.Promise.resolve(isLoggedIn);
                   })
              );
         | true => Js.Promise.resolve(isLoggedIn)
         };
       })
    |> ignore;
    OneGraphAuth.isLoggedIn(self.state.oneAuth, "eventil")
    |> Js.Promise.then_((isLoggedIn: bool) => {
         Js.log2("User is logged in to eventil: ", isLoggedIn);
         self.send(SetEventilLoggedIn(isLoggedIn));
         switch (isLoggedIn) {
         | false =>
           Js.log("Forcing Eventil login");
           OneGraphAuth.login(self.state.oneAuth, "eventil")
           |> Js.Promise.then_(() =>
                OneGraphAuth.isLoggedIn(self.state.oneAuth, "eventil")
                |> Js.Promise.then_(isLoggedIn => {
                     Js.log2(
                       "User is logged in to eventil after login: ",
                       isLoggedIn,
                     );
                     self.send(SetEventilLoggedIn(isLoggedIn));
                     Js.Promise.resolve(isLoggedIn);
                   })
              );
         | true => Js.Promise.resolve(isLoggedIn)
         };
       })
    |> ignore;
  },
  render: ({state, send: _send}) =>
    ReasonReact.(
      switch (true, true, state.failed, state.videoId) {
      | (_, _, true, _) => string("Not on a Youtube site")
      | (_, _, _, None) =>
        string(
          "No video detected: "
          ++ Option.default("unknown url", state.currentUrl),
        )
      | (false, _, _, _) => string("Please log with Github, ok?")
      /* | (_, false, _, _) => string("Please log with Twitter") */
      | (true, _, _, _) =>
        <div>
          <input
            defaultValue=state.eventId
            onKeyDown=(
              event =>
                if (ReactEventRe.Keyboard.keyCode(event) === 13) {
                  ReactEventRe.Keyboard.preventDefault(event);
                  _send(
                    SetEventId(
                      ReactDOMRe.domElementToObj(
                        ReactEventRe.Keyboard.target(event),
                      )##value,
                    ),
                  );
                } else {
                  ();
                }
            )
            _type="text"
          />
          <h1> (string("PowerTiller")) </h1>
          <p>
            (
              string(
                "Logged into YouTube: "
                ++ string_of_bool(state.isYouTubeLoggedIn),
              )
            )
          </p>
          <p>
            (
              string(
                "Logged into Eventil: "
                ++ string_of_bool(state.isEventilLoggedIn),
              )
            )
          </p>
          <Event eventId=state.eventId />
        </div>
      }
    ),
};
