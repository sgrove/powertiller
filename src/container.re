module Layout = Antd.Layout;
open Antd.Grid;

type action =
  | SetEventId(string)
  | SetVideoId(string)
  | SetUrl(option(string))
  | SetEventilLoggedIn(bool)
  | SetGithubLoggedIn(bool)
  | SetGoogleLoggedIn(bool)
  | SetTwitterLoggedIn(bool)
  | SelectPresentation(Types.presentation)
  | Fail;

type state = {
  oneAuth: Js.t({.}),
  videoId: option(string),
  currentUrl: option(string),
  collapsed: bool,
  failed: bool,
  eventId: string,
  selectedPresentation: option(Types.presentation),
  isEventilLoggedIn: bool,
  isGithubLoggedIn: bool,
  isYouTubeLoggedIn: bool,
  isTwitterLoggedIn: bool,
};

let component = ReasonReact.reducerComponent("Page");

let colSize = span => Col.FullColSize(makeColSize(~span, ()));

let checkLoggedIn = (send, state: state, service) =>
  Js.(
    OneGraphAuth.isLoggedIn(state.oneAuth, service)
    |> Promise.then_((isLoggedIn: bool) => {
         log2("User is logged in to eventil: ", isLoggedIn);
         send(SetEventilLoggedIn(isLoggedIn));
         Promise.resolve();
       })
    |> ignore
  );

let logIn = (send, state: state, service) =>
  Js.(
    OneGraphAuth.login(state.oneAuth, service)
    |> Promise.then_(() =>
         OneGraphAuth.isLoggedIn(state.oneAuth, service)
         |> Promise.then_(isLoggedIn => {
              log3(
                "User is logged in to service after login: ",
                service,
                isLoggedIn,
              );
              send(SetGoogleLoggedIn(isLoggedIn));
              Promise.resolve(isLoggedIn);
            })
       )
    |> ignore
  );

let footer =
  ReasonReact.(
    <div> (string("Made with lots and lots of tea on OneGraph")) </div>
  );

let header = (state, send) =>
  ReasonReact.(
    <Row>
      <Col xs=(colSize(20)) lg=(colSize(8))>
        <div
          className="logo"
          style=(ReactDOMRe.Style.make(~width="200px", ~color="white", ()))>
          <h1 style=(ReactDOMRe.Style.make(~color="white", ()))>
            (string("PowerTiller"))
          </h1>
        </div>
      </Col>
      <Col xs=(colSize(0)) lg=(colSize(16))>
        <div
          style=(
            ReactDOMRe.Style.make(
              ~display="flex",
              ~justifyContent="flex-end",
              (),
            )
          )>
          <Antd.Menu
            selectable=false
            theme=`Dark
            mode=`Horizontal
            inlineIndent=12
            style=(ReactDOMRe.Style.make(~lineHeight="64px", ()))
          />
          <input
            defaultValue=state.eventId
            onKeyDown=(
              event =>
                ReactEventRe.Keyboard.(
                  switch (keyCode(event)) {
                  | 13 =>
                    preventDefault(event);
                    let element = target(event) |> ReactDOMRe.domElementToObj;
                    send(SetEventId(element##value));
                  | _ => ()
                  }
                )
            )
            _type="text"
          />
          <button
            disabled=state.isEventilLoggedIn
            onClick=(_event => logIn(send, state, "eventil"))>
            <Antd.Icon type_=Antd.IconName.github />
          </button>
          <button
            disabled=state.isYouTubeLoggedIn
            onClick=(_event => logIn(send, state, "youtube"))>
            <Antd.Icon type_=Antd.IconName.youtube />
          </button>
        </div>
      </Col>
      <Col xs=(colSize(4)) lg=(colSize(0))>
        <div
          style=(
            ReactDOMRe.Style.make(
              ~display="flex",
              ~justifyContent="flex-end",
              ~alignItems="center",
              ~height="64px",
              ~position="relative",
              (),
            )
          )
        />
      </Col>
    </Row>
  );

let make = (~forcedVideoId=?, _children) => {
  ...component,
  initialState: () => {
    eventId: "nordic-js-2017",
    oneAuth: Client.auth,
    videoId: None,
    failed: false,
    currentUrl: None,
    collapsed: false,
    selectedPresentation: None,
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
    | SelectPresentation(presentation) =>
      Update({...state, selectedPresentation: Some(presentation)})

    | Fail => ReasonReact.Update({...state, failed: true})
    },
  didMount: self => {
    open Js.Promise;
    open Js;
    switch (forcedVideoId) {
    | None => ()
    | Some(videoId) => self.send(SetVideoId(videoId))
    };
    checkLoggedIn(self.send, self.state, "youtube");
    checkLoggedIn(self.send, self.state, "eventil");
    ();
  },
  render: ({state, send}) => {
    open ReasonReact;
    ();
    <div>
      <Layout>
        <Layout.Header> (header(state, send)) </Layout.Header>
        <Layout>
          <Layout.Sider
            style=(ReactDOMRe.Style.make(~color="hsla(0,0%,100%,.65)", ()))>
            (
              switch (state.failed, state.videoId) {
              | (true, _) => string("Not on a Youtube site")
              | (_, None) =>
                string(
                  "No video detected: "
                  ++ Option.default("unknown url", state.currentUrl),
                )
              | (_, _) =>
                <Event
                  eventId=state.eventId
                  onPresentationSelected=(
                    presentation => send(SelectPresentation(presentation))
                  )
                />
              }
            )
          </Layout.Sider>
          <Layout.Content>
            (
              switch (state.selectedPresentation) {
              | None => null
              | Some(presentation) =>
                let term = Types.presentationToQueryTerm(presentation);
                <Talk term presentation />;
              }
            )
          </Layout.Content>
        </Layout>
        <Layout.Footer> footer </Layout.Footer>
      </Layout>
    </div>;
  },
};
