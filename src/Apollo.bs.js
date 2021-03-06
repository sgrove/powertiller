// Generated by BUCKLESCRIPT VERSION 4.0.5, PLEASE EDIT WITH CARE
'use strict';

var ApolloLinks = require("reason-apollo/src/ApolloLinks.bs.js");
var ReasonApollo = require("reason-apollo/src/ReasonApollo.bs.js");
var ApolloInMemoryCache = require("reason-apollo/src/ApolloInMemoryCache.bs.js");

var inMemoryCache = ApolloInMemoryCache.createInMemoryCache((function (obj) {
        return obj.id;
      }), undefined, /* () */0);

var httpLink = ApolloLinks.createHttpLink("http://localhost:3010/graphql", undefined, undefined, undefined, undefined, undefined, /* () */0);

var apolloClient = ReasonApollo.createApolloClient(httpLink, inMemoryCache, undefined, undefined, undefined, undefined, /* () */0);

var Client = /* module */[/* apolloClient */apolloClient];

exports.inMemoryCache = inMemoryCache;
exports.httpLink = httpLink;
exports.Client = Client;
/* inMemoryCache Not a pure module */
