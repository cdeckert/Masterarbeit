'use strict'

###*
 # @ngdoc function
 # @name viewerApp.controller:MainCtrl
 # @description
 # # MainCtrl
 # Controller of the viewerApp
###
angular.module('viewerApp')
  .controller 'MainCtrl', ($scope) ->
    $scope.awesomeThings = [
      'HTML5 Boilerplate'
      'AngularJS'
      'Karma'
    ]
