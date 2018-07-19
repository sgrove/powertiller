type config;

[@bs.obj]
external create :
  (
    ~appId: string,
    ~oauthFinishPath: string=?,
    ~oneGraphOrigin: string=?,
    unit
  ) =>
  config =
  "";

[@bs.deriving jsConverter]
type service = [ | `YouTube | [@bs.as "github"] `GitHub | `Eventil];

[@bs.new] [@bs.module "onegraph-auth"]
external make : config => Js.t({..}) = "default";

[@bs.send] external login : (Js.t({..}), string) => Js.Promise.t('a) = "";

[@bs.send] external logout : (Js.t({..}), string) => Js.Promise.t('a) = "";

[@bs.send]
external isLoggedIn : (Js.t({..}), string) => Js.Promise.t(bool) = "";
