// Generated by BUCKLESCRIPT VERSION 4.0.5, PLEASE EDIT WITH CARE
'use strict';

var Js_mapperRt = require("bs-platform/lib/js/js_mapperRt.js");

var jsMapperConstantArray = /* array */[
  /* tuple */[
    -739506595,
    "Eventil"
  ],
  /* tuple */[
    -330023197,
    "YouTube"
  ],
  /* tuple */[
    625823715,
    "github"
  ]
];

function serviceToJs(param) {
  return Js_mapperRt.binarySearch(3, param, jsMapperConstantArray);
}

function serviceFromJs(param) {
  return Js_mapperRt.revSearch(3, jsMapperConstantArray, param);
}

exports.serviceToJs = serviceToJs;
exports.serviceFromJs = serviceFromJs;
/* No side effect */
