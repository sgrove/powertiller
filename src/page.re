type action =
  | SetEventId(string)
  | SetVideoId(string)
  | SetUrl(option(string))
  | SetGithubLoggedIn(bool)
  | SetGoogleLoggedIn(bool)
  | SetTwitterLoggedIn(bool)
  | Fail;

type state = {
  githubAuth: OneGraphAuth.t,
  googleAuth: OneGraphAuth.t,
  twitterAuth: OneGraphAuth.t,
  videoId: option(string),
  currentUrl: option(string),
  failed: bool,
  eventId: string,
  isGithubLoggedIn: bool,
  isGoogleLoggedIn: bool,
  isTwitterLoggedIn: bool
};

let component = ReasonReact.reducerComponent("Page");

let make = (~forcedVideoId=?, _children) => {
  ...component,
  initialState: () => {
    eventId: "nordic-js-2017",
    githubAuth:
      OneGraphAuth.(
        makeConfig(
          ~service="github",
          ~appId=Config.appId,
          ~oneGraphOrigin="https://serve.onegraph.com",
          ~oauthFinishPath="/src/popup.html",
          ()
        )
        |> make
      ),
    googleAuth:
      OneGraphAuth.(
        makeConfig(
          ~service="google",
          ~appId=Config.appId,
          ~oneGraphOrigin="https://serve.onegraph.com",
          ~oauthFinishPath="/src/popup.html",
          ()
        )
        |> make
      ),
    twitterAuth:
      OneGraphAuth.(
        makeConfig(
          ~service="twitter",
          ~appId=Config.appId,
          ~oneGraphOrigin="https://serve.onegraph.com",
          ~oauthFinishPath="/src/popup.html",
          ()
        )
        |> make
      ),
    videoId: None,
    failed: false,
    currentUrl: None,
    isGithubLoggedIn: false,
    isGoogleLoggedIn: false,
    isTwitterLoggedIn: false
  },
  reducer: (action, state) =>
    switch action {
    | SetVideoId(videoId) =>
      ReasonReact.Update({...state, videoId: Some(videoId)})
    | SetEventId(eventId) => ReasonReact.Update({...state, eventId})
    | SetUrl(url) =>
      switch url {
      | None => ReasonReact.Update({...state, currentUrl: None})
      | Some(url) =>
        let videoId: option(string) =
          switch (Js.String.match([%bs.re "/v=([a-zA-Z0-9-_]+)/"], url)) {
          | None => None
          | Some(matches) => Some(matches[1])
          };
        ReasonReact.Update({...state, currentUrl: Some(url), videoId});
      }
    | SetGithubLoggedIn(isLoggedIn) =>
      ReasonReact.Update({...state, isGithubLoggedIn: isLoggedIn})
    | SetGoogleLoggedIn(isLoggedIn) =>
      ReasonReact.Update({...state, isGoogleLoggedIn: isLoggedIn})
    | SetTwitterLoggedIn(isLoggedIn) =>
      ReasonReact.Update({...state, isTwitterLoggedIn: isLoggedIn})
    | Fail => ReasonReact.Update({...state, failed: true})
    },
  didMount: self => {
    try (
      Chrome.Tabs.getActive(activeTab => {
        Js.log2("Active tab:", activeTab);
        self.send(SetUrl(Js.Nullable.to_opt(activeTab##url)));
      })
    ) {
    | _ =>
      switch forcedVideoId {
      | None => ()
      | Some(videoId) => self.send(SetVideoId(videoId))
      }
    };
    OneGraphAuth.isLoggedIn(self.state.googleAuth)
    |> Js.Promise.then_((isLoggedIn: Js.boolean) => {
         Js.log2("User is logged in to Google: ", isLoggedIn);
         let isLoggedIn = Js.to_bool(isLoggedIn);
         self.send(SetGoogleLoggedIn(isLoggedIn));
         switch isLoggedIn {
         | false =>
           Js.log("Forcing twitter login");
           OneGraphAuth.login(self.state.googleAuth)
           |> Js.Promise.then_(() =>
                OneGraphAuth.isLoggedIn(self.state.googleAuth)
                |> Js.Promise.then_((isLoggedIn: Js.boolean) => {
                     let isLoggedIn = Js.to_bool(isLoggedIn);
                     Js.log2(
                       "User is logged in to google after login: ",
                       isLoggedIn
                     );
                     self.send(SetGoogleLoggedIn(isLoggedIn));
                     Js.Promise.resolve(isLoggedIn);
                   })
              );
         | true => Js.Promise.resolve(isLoggedIn)
         };
       })
    |> ignore;
    ReasonReact.NoUpdate;
  },
  render: ({state, send: _send}) =>
    switch (true, true, state.failed, state.videoId) {
    | (_, _, true, _) => Utils.s("Not on a Youtube site")
    | (_, _, _, None) =>
      Utils.s(
        "No video detected: " ++ Utils.default("unknown url", state.currentUrl)
      )
    | (false, _, _, _) => Utils.s("Please log with Github, ok?")
    /* | (_, false, _, _) => Utils.s("Please log with Twitter") */
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
                      ReactEventRe.Keyboard.target(event)
                    )##value
                  )
                );
              } else {
                ();
              }
          )
          _type="text"
        />
        <h1> (Utils.s("PowerTiller")) </h1>
        <Event eventId=state.eventId />
      </div>
    }
};
