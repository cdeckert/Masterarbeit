'use strict'

###*
 # @ngdoc function
 # @name viewerApp.controller:AboutCtrl
 # @description
 # # AboutCtrl
 # Controller of the viewerApp
###
angular.module('viewerApp')
  .controller 'AboutCtrl', ($scope) ->
    $scope.awesomeThings = [
      'HTML5 Boilerplate'
      'AngularJS'
      'Karma'
    ]
