// Generated by BUCKLESCRIPT VERSION 4.0.5, PLEASE EDIT WITH CARE
'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Js_exn = require("bs-platform/lib/js/js_exn.js");
var Js_dict = require("bs-platform/lib/js/js_dict.js");
var Js_json = require("bs-platform/lib/js/js_json.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Js_primitive = require("bs-platform/lib/js/js_primitive.js");
var ReasonApollo = require("reason-apollo/src/ReasonApollo.bs.js");
var Option$ReactTemplate = require("./option.bs.js");
var VideoSetter$ReactTemplate = require("./videoSetter.bs.js");
var VideoPreview$ReactTemplate = require("./videoPreview.bs.js");

var ppx_printed_query = "query findPotentialVideos($q: String!)  {\nyouTubeSearch(q: $q, maxResults: 10)  {\nitems  {\nedges  {\nnode  {\nid  \nsnippet  {\ntitle  \ndescription  \n}\n\n}\n\n}\n\n}\n\n}\n\n}\n";

function parse(value) {
  var match = Js_json.decodeObject(value);
  if (match !== undefined) {
    var match$1 = Js_primitive.valFromOption(match)["youTubeSearch"];
    var tmp;
    if (match$1 !== undefined) {
      var match$2 = Js_json.decodeNull(match$1);
      if (match$2 !== undefined) {
        tmp = undefined;
      } else {
        var match$3 = Js_json.decodeObject(match$1);
        var tmp$1;
        if (match$3 !== undefined) {
          var match$4 = Js_primitive.valFromOption(match$3)["items"];
          var tmp$2;
          if (match$4 !== undefined) {
            var match$5 = Js_json.decodeObject(match$4);
            if (match$5 !== undefined) {
              var match$6 = Js_primitive.valFromOption(match$5)["edges"];
              var tmp$3;
              if (match$6 !== undefined) {
                var match$7 = Js_json.decodeArray(match$6);
                tmp$3 = match$7 !== undefined ? match$7.map((function (value) {
                          var match = Js_json.decodeObject(value);
                          if (match !== undefined) {
                            var match$1 = Js_primitive.valFromOption(match)["node"];
                            var tmp;
                            if (match$1 !== undefined) {
                              var match$2 = Js_json.decodeObject(match$1);
                              if (match$2 !== undefined) {
                                var value$1 = Js_primitive.valFromOption(match$2);
                                var match$3 = value$1["id"];
                                var tmp$1;
                                if (match$3 !== undefined) {
                                  var match$4 = Js_json.decodeString(match$3);
                                  tmp$1 = match$4 !== undefined ? match$4 : Js_exn.raiseError("graphql_ppx: Expected string, got " + JSON.stringify(match$3));
                                } else {
                                  tmp$1 = Js_exn.raiseError("graphql_ppx: Field id on type YoutubeSearchNode is missing");
                                }
                                var match$5 = value$1["snippet"];
                                var tmp$2;
                                if (match$5 !== undefined) {
                                  var match$6 = Js_json.decodeObject(match$5);
                                  if (match$6 !== undefined) {
                                    var value$2 = Js_primitive.valFromOption(match$6);
                                    var match$7 = value$2["title"];
                                    var tmp$3;
                                    if (match$7 !== undefined) {
                                      var match$8 = Js_json.decodeString(match$7);
                                      tmp$3 = match$8 !== undefined ? match$8 : Js_exn.raiseError("graphql_ppx: Expected string, got " + JSON.stringify(match$7));
                                    } else {
                                      tmp$3 = Js_exn.raiseError("graphql_ppx: Field title on type YoutubeSearchNodeSnippet is missing");
                                    }
                                    var match$9 = value$2["description"];
                                    var tmp$4;
                                    if (match$9 !== undefined) {
                                      var match$10 = Js_json.decodeString(match$9);
                                      tmp$4 = match$10 !== undefined ? match$10 : Js_exn.raiseError("graphql_ppx: Expected string, got " + JSON.stringify(match$9));
                                    } else {
                                      tmp$4 = Js_exn.raiseError("graphql_ppx: Field description on type YoutubeSearchNodeSnippet is missing");
                                    }
                                    tmp$2 = {
                                      title: tmp$3,
                                      description: tmp$4
                                    };
                                  } else {
                                    tmp$2 = Js_exn.raiseError("graphql_ppx: Object is not a value");
                                  }
                                } else {
                                  tmp$2 = Js_exn.raiseError("graphql_ppx: Field snippet on type YoutubeSearchNode is missing");
                                }
                                tmp = {
                                  id: tmp$1,
                                  snippet: tmp$2
                                };
                              } else {
                                tmp = Js_exn.raiseError("graphql_ppx: Object is not a value");
                              }
                            } else {
                              tmp = Js_exn.raiseError("graphql_ppx: Field node on type YoutubeEdge is missing");
                            }
                            return {
                                    node: tmp
                                  };
                          } else {
                            return Js_exn.raiseError("graphql_ppx: Object is not a value");
                          }
                        })) : Js_exn.raiseError("graphql_ppx: Expected array, got " + JSON.stringify(match$6));
              } else {
                tmp$3 = Js_exn.raiseError("graphql_ppx: Field edges on type YoutubeVideoSearchItemContainer is missing");
              }
              tmp$2 = {
                edges: tmp$3
              };
            } else {
              tmp$2 = Js_exn.raiseError("graphql_ppx: Object is not a value");
            }
          } else {
            tmp$2 = Js_exn.raiseError("graphql_ppx: Field items on type YoutubeVideoSearchResult is missing");
          }
          tmp$1 = {
            items: tmp$2
          };
        } else {
          tmp$1 = Js_exn.raiseError("graphql_ppx: Object is not a value");
        }
        tmp = Js_primitive.some(tmp$1);
      }
    } else {
      tmp = undefined;
    }
    return {
            youTubeSearch: tmp
          };
  } else {
    return Js_exn.raiseError("graphql_ppx: Object is not a value");
  }
}

function make(q, _) {
  return {
          query: ppx_printed_query,
          variables: Js_dict.fromArray(/* array */[/* tuple */[
                  "q",
                  q
                ]]),
          parse: parse
        };
}

function makeWithVariables(variables) {
  var q = variables.q;
  return {
          query: ppx_printed_query,
          variables: Js_dict.fromArray(/* array */[/* tuple */[
                  "q",
                  q
                ]]),
          parse: parse
        };
}

function ret_type() {
  return /* module */[];
}

var MT_Ret = /* module */[];

var FindPotentialVideosQuery = /* module */[
  /* ppx_printed_query */ppx_printed_query,
  /* query */ppx_printed_query,
  /* parse */parse,
  /* make */make,
  /* makeWithVariables */makeWithVariables,
  /* ret_type */ret_type,
  /* MT_Ret */MT_Ret
];

var component = ReasonReact.reducerComponent("VideoSelector");

var Query = ReasonApollo.CreateQuery([
      ppx_printed_query,
      parse
    ]);

function make$1(term, presentationId, _) {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */component[/* didMount */4],
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (self) {
              console.log("term", term);
              var videosQuery = make(term, /* () */0);
              console.log("FPVQ", videosQuery);
              return ReasonReact.element(undefined, undefined, Curry.app(Query[/* make */3], [
                              Js_primitive.some(videosQuery.variables),
                              undefined,
                              undefined,
                              undefined,
                              undefined,
                              undefined,
                              undefined,
                              undefined,
                              undefined,
                              (function (param) {
                                  var result = param[/* result */0];
                                  if (typeof result === "number") {
                                    return React.createElement("div", undefined, "Loading");
                                  } else if (result.tag) {
                                    var result$1 = result[0];
                                    var match = result$1.youTubeSearch;
                                    return React.createElement("div", undefined, React.createElement("pre", undefined, Option$ReactTemplate.$$default("Baffled....", Js_primitive.undefined_to_opt(JSON.stringify(result$1)))), React.createElement("ul", undefined, match !== undefined ? $$Array.map((function (edge) {
                                                            var match = self[/* state */1][/* selectedVideo */2];
                                                            var tmp;
                                                            if (match !== undefined) {
                                                              var selectedVideo = Js_primitive.valFromOption(match);
                                                              tmp = selectedVideo.id === edge.node.id ? React.createElement("div", undefined, ReasonReact.element(undefined, undefined, VideoSetter$ReactTemplate.make(presentationId, selectedVideo.id, /* array */[])), ReasonReact.element(undefined, undefined, VideoPreview$ReactTemplate.make(selectedVideo.id, /* array */[]))) : null;
                                                            } else {
                                                              tmp = null;
                                                            }
                                                            return React.createElement("li", {
                                                                        onClick: (function () {
                                                                            return Curry._1(self[/* send */3], /* SelectSearchNode */[edge.node]);
                                                                          })
                                                                      }, edge.node.snippet.title + (" - " + edge.node.snippet.description), tmp);
                                                          }), Js_primitive.valFromOption(match).items.edges) : /* array */["No search results"]));
                                  } else {
                                    return React.createElement("div", undefined, Option$ReactTemplate.$$default("Some error", Js_primitive.undefined_to_opt(JSON.stringify(result[0]))));
                                  }
                                })
                            ]));
            }),
          /* initialState */(function () {
              return /* record */[
                      /* count */0,
                      /* show */false,
                      /* selectedVideo */undefined
                    ];
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */(function (action, state) {
              if (typeof action === "number") {
                if (action !== 0) {
                  return /* Update */Block.__(0, [/* record */[
                              /* count */state[/* count */0],
                              /* show */!state[/* show */1],
                              /* selectedVideo */state[/* selectedVideo */2]
                            ]]);
                } else {
                  return /* Update */Block.__(0, [/* record */[
                              /* count */state[/* count */0] + 1 | 0,
                              /* show */state[/* show */1],
                              /* selectedVideo */state[/* selectedVideo */2]
                            ]]);
                }
              } else {
                return /* Update */Block.__(0, [/* record */[
                            /* count */state[/* count */0],
                            /* show */state[/* show */1],
                            /* selectedVideo */Js_primitive.some(action[0])
                          ]]);
              }
            }),
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

exports.FindPotentialVideosQuery = FindPotentialVideosQuery;
exports.component = component;
exports.Query = Query;
exports.make = make$1;
/* component Not a pure module */
