// Generated by BUCKLESCRIPT VERSION 3.1.5, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Js_dict = require("bs-platform/lib/js/js_dict.js");
var Js_json = require("bs-platform/lib/js/js_json.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Js_primitive = require("bs-platform/lib/js/js_primitive.js");
var ReasonApollo = require("reason-apollo/src/ReasonApollo.bs.js");
var Caml_exceptions = require("bs-platform/lib/js/caml_exceptions.js");
var Utils$ReactTemplate = require("./utils.bs.js");
var Option$ReactTemplate = require("./option.bs.js");

var Graphql_error = Caml_exceptions.create("VideoSetter-ReactTemplate.SetPresentationVideoIdMutation.Graphql_error");

var ppx_printed_query = "mutation setEventilPresentationVideoId($presentationId: String!, $youTubeVideoId: String!)  {\neventil  {\nsetVideoId(id: $presentationId, youtube_id: $youTubeVideoId)  {\ndraft  {\ntitle  \n}\n}\n}\n}";

function parse(value) {
  var match = Js_json.decodeObject(value);
  if (match) {
    var match$1 = match[0]["eventil"];
    var tmp;
    if (match$1 !== undefined) {
      var match$2 = Js_json.decodeNull(match$1);
      if (match$2) {
        tmp = /* None */0;
      } else {
        var match$3 = Js_json.decodeObject(match$1);
        var tmp$1;
        if (match$3) {
          var match$4 = match$3[0]["setVideoId"];
          var tmp$2;
          if (match$4 !== undefined) {
            var match$5 = Js_json.decodeNull(match$4);
            if (match$5) {
              tmp$2 = /* None */0;
            } else {
              var match$6 = Js_json.decodeObject(match$4);
              var tmp$3;
              if (match$6) {
                var match$7 = match$6[0]["draft"];
                var tmp$4;
                if (match$7 !== undefined) {
                  var match$8 = Js_json.decodeObject(match$7);
                  if (match$8) {
                    var match$9 = match$8[0]["title"];
                    var tmp$5;
                    if (match$9 !== undefined) {
                      var match$10 = Js_json.decodeNull(match$9);
                      if (match$10) {
                        tmp$5 = /* None */0;
                      } else {
                        var match$11 = Js_json.decodeString(match$9);
                        var tmp$6;
                        if (match$11) {
                          tmp$6 = match$11[0];
                        } else {
                          throw [
                                Graphql_error,
                                "Expected string, got " + JSON.stringify(match$9)
                              ];
                        }
                        tmp$5 = /* Some */[tmp$6];
                      }
                    } else {
                      tmp$5 = /* None */0;
                    }
                    tmp$4 = {
                      title: tmp$5
                    };
                  } else {
                    throw [
                          Graphql_error,
                          "Object is not a value"
                        ];
                  }
                } else {
                  throw [
                        Graphql_error,
                        "Field draft on type EventilPresentation is missing"
                      ];
                }
                tmp$3 = {
                  draft: tmp$4
                };
              } else {
                throw [
                      Graphql_error,
                      "Object is not a value"
                    ];
              }
              tmp$2 = /* Some */[tmp$3];
            }
          } else {
            tmp$2 = /* None */0;
          }
          tmp$1 = {
            setVideoId: tmp$2
          };
        } else {
          throw [
                Graphql_error,
                "Object is not a value"
              ];
        }
        tmp = /* Some */[tmp$1];
      }
    } else {
      tmp = /* None */0;
    }
    return {
            eventil: tmp
          };
  } else {
    throw [
          Graphql_error,
          "Object is not a value"
        ];
  }
}

function json_of_optional(encoder, value) {
  if (value) {
    return Curry._1(encoder, value[0]);
  } else {
    return null;
  }
}

function json_of_array(encoder, value) {
  return value.map(Curry.__1(encoder));
}

function json_of_String(value) {
  return value;
}

function make(presentationId, youTubeVideoId, _) {
  return {
          query: ppx_printed_query,
          variables: Js_dict.fromList(/* :: */[
                /* tuple */[
                  "presentationId",
                  presentationId
                ],
                /* :: */[
                  /* tuple */[
                    "youTubeVideoId",
                    youTubeVideoId
                  ],
                  /* [] */0
                ]
              ]),
          parse: parse
        };
}

function makeWithVariables(variables) {
  var presentationId = variables.presentationId;
  var youTubeVideoId = variables.youTubeVideoId;
  return {
          query: ppx_printed_query,
          variables: Js_dict.fromList(/* :: */[
                /* tuple */[
                  "presentationId",
                  presentationId
                ],
                /* :: */[
                  /* tuple */[
                    "youTubeVideoId",
                    youTubeVideoId
                  ],
                  /* [] */0
                ]
              ]),
          parse: parse
        };
}

function ret_type() {
  return /* module */[];
}

var MT_Ret = /* module */[];

var SetPresentationVideoIdMutation = /* module */[
  /* Graphql_error */Graphql_error,
  /* ppx_printed_query */ppx_printed_query,
  /* query */ppx_printed_query,
  /* parse */parse,
  /* json_of_optional */json_of_optional,
  /* json_of_array */json_of_array,
  /* json_of_String */json_of_String,
  /* make */make,
  /* makeWithVariables */makeWithVariables,
  /* ret_type */ret_type,
  /* MT_Ret */MT_Ret
];

var mutationComponent = ReasonReact.statelessComponent("Video Setter");

var Mutation = ReasonApollo.CreateMutation([
      ppx_printed_query,
      parse
    ]);

function make$1(presentationId, videoId, _) {
  return /* record */[
          /* debugName */mutationComponent[/* debugName */0],
          /* reactClassInternal */mutationComponent[/* reactClassInternal */1],
          /* handedOffState */mutationComponent[/* handedOffState */2],
          /* willReceiveProps */mutationComponent[/* willReceiveProps */3],
          /* didMount */mutationComponent[/* didMount */4],
          /* didUpdate */mutationComponent[/* didUpdate */5],
          /* willUnmount */mutationComponent[/* willUnmount */6],
          /* willUpdate */mutationComponent[/* willUpdate */7],
          /* shouldUpdate */mutationComponent[/* shouldUpdate */8],
          /* render */(function () {
              return ReasonReact.element(/* None */0, /* None */0, Curry._4(Mutation[/* make */4], /* None */0, /* None */0, /* None */0, (function (mutation, param) {
                                var result = param[/* result */0];
                                if (typeof result === "number") {
                                  if (result === 0) {
                                    return React.createElement("div", undefined, Utils$ReactTemplate.s("Loading mutation result"));
                                  } else {
                                    return React.createElement("div", undefined, React.createElement("button", {
                                                    onClick: (function () {
                                                        var setVideoMutation = make(presentationId, videoId, /* () */0);
                                                        Curry._3(mutation, /* Some */[setVideoMutation.variables], /* None */0, /* () */0);
                                                        return /* () */0;
                                                      })
                                                  }, Utils$ReactTemplate.s("Set this video")));
                                  }
                                } else if (result.tag) {
                                  return React.createElement("div", undefined, Utils$ReactTemplate.s(Utils$ReactTemplate.$$default("Couldn't get result", Js_primitive.undefined_to_opt(JSON.stringify(result[0])))));
                                } else {
                                  return React.createElement("div", undefined, Utils$ReactTemplate.s(Option$ReactTemplate.$$default("Some error", Js_primitive.undefined_to_opt(JSON.stringify(result[0])))));
                                }
                              })));
            }),
          /* initialState */mutationComponent[/* initialState */10],
          /* retainedProps */mutationComponent[/* retainedProps */11],
          /* reducer */mutationComponent[/* reducer */12],
          /* subscriptions */mutationComponent[/* subscriptions */13],
          /* jsElementWrapped */mutationComponent[/* jsElementWrapped */14]
        ];
}

exports.SetPresentationVideoIdMutation = SetPresentationVideoIdMutation;
exports.mutationComponent = mutationComponent;
exports.Mutation = Mutation;
exports.make = make$1;
/* mutationComponent Not a pure module */
