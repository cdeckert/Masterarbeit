'use strict'

###*
 # @ngdoc overview
 # @name viewerApp
 # @description
 # # viewerApp
 #
 # Main module of the application.
###
angular
  .module('viewerApp', [
    'ngAnimate',
    'ngCookies',
    'ngResource',
    'ngRoute',
    'ngSanitize',
    'ngTouch',
    'ui.keypress'
  ])
  .config ($routeProvider) ->
    $routeProvider
      .when '/',
        templateUrl: 'views/main.html'
        controller: 'MainCtrl'
      .when '/generator',
        templateUrl: 'views/generator.html'
        controller: 'GeneratorCtrl'
      .otherwise
        redirectTo: '/'

