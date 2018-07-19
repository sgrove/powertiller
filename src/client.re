[@bs.module "apollo-boost"] [@bs.new]
external boost : Js.t({..}) => ApolloClient.generatedApolloClient = "default";

open ApolloLinks;

open ApolloInMemoryCache;

/* Define type for InMemoryCache's dataIdFromObject option  */
type dataObject = {
  .
  "__typename": string,
  "id": string,
  "key": string,
};

let logout = () => ();

let uri =
  Printf.sprintf("http://serve.onegraph.com/dynamic?app_id=%s", Config.appId);

/* Create an HTTP Link */
let _httpLink = createHttpLink(~uri, ~credentials="include", ());

/* Create a Link that puts an Authorization header in context */
let contextHandler = () => {
  let headers = {
    "headers": {
      "show_beta_schema": {j|true|j},
    },
  };
  headers;
};

let authLink = createContextLink(contextHandler);

/* Create a Link that handles 401 error responses */
let errorHandler = errorResponse =>
  switch (errorResponse##networkError) {
  | Some(error) =>
    if (error##statusCode == 401) {
      logout();
    } else {
      ();
    }
  | None => ()
  };

let errorLink = createErrorLink(errorHandler);

let _inMemoryCache =
  createInMemoryCache(
    ~dataIdFromObject=
      (obj: dataObject) =>
        if (obj##__typename === "Organization") {
          obj##key;
        } else {
          obj##id;
        },
    (),
  );

/* Create an InMemoryCache */
let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();

/* Create an HTTP Link */
let httpLink = ApolloLinks.createHttpLink(~uri, ~credentials="include", ());

/* request: operation => operation.setContext({headers: auth.authHeaders()}), */

/* Create the ApolloClient */
let instance =
  ReasonApollo.createApolloClient(
    ~link=from([|authLink, errorLink, httpLink|]),
    ~cache=inMemoryCache,
    (),
  );

let auth =
  OneGraphAuth.(
    create(~appId=Config.appId, ~oauthFinishPath="/src/popup.html", ())
    |> make
  );

let instance =
  boost({
    "uri": "https://serve.onegraph.com/dynamic?app_id=" ++ Config.appId,
    "request": operation =>
      operation##setContext({"headers": auth##authHeaders()}),
  });
