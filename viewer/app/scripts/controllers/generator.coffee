'use strict'

###*
 # @ngdoc function
 # @name viewerApp.controller:GeneratorCtrl
 # @description
 # # GeneratorCtrl
 # Controller of the viewerApp
###
angular.module('viewerApp')
  .controller 'GeneratorCtrl', ($scope) ->

    $scope.relations = [{relation: 1, cardinality: ''}]
    $scope.joinEdges = [{id: 1, from: '', to: '', selectivity: ''}]
    $scope.algorithms = []

    $scope.potentialRuelSets = ["RS_0", "RS_1", "RS_2", "GraphRule"]
    $scope.configFile = ["aaa"]


    $scope.addRelationByTab = ($event,relation)->
    	if(relation == $scope.relations.length)
    		$scope.addRelation()


    $scope.addRelation = ->
    	$scope.relations.push {
    		relation: $scope.relations.length + 1
    		cardinality: ''
    	}

    $scope.addJoinEdge = ->
    	$scope.joinEdges.push {
    		id: $scope.joinEdges.length+1, from: '', to: '', selectivity: ''
    	}
    $scope.addJoinEdgeByTab = ($event,edge)->
    	if(edge == $scope.joinEdges.length)
    		$scope.addJoinEdge()

    $scope.clickAlgo = (algo)->
    	console.log $scope.containsAlgo algo
    	if  !$scope.containsAlgo algo
    		$scope.algorithms.push algo
    	else
    		$scope.algorithms.splice($scope.algorithms.indexOf algo, 1)

    $scope.containsAlgo = (algo)->
    	(($scope.algorithms.indexOf(algo)) != -1)