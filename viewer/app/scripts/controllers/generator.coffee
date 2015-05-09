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
	$scope.configFile = []

	$scope.nodes = [{op: "scan", l: 1, relations: 1}]
	$scope.toBeJoined = null

	$scope.addRelationByTab = ($event,relation)->
		if(relation == $scope.relations.length)
			$scope.addRelation()

	$scope.join = (node) ->
		node.marked = true
		if $scope.toBeJoined?
			$scope.nodes.push {op: "join", "l": $scope.toBeJoined, r: node, relations: "JOIN("+$scope.toBeJoined.relations+", "+ node.relations+")"}
			node.hide = true
			$scope.toBeJoined.hide = true
			$scope.toBeJoined = null

		else
			$scope.toBeJoined = node

	$scope.isValidForSubmission = ->
		validNodes = []
		for n in $scope.nodes
			validNodes.push n if not n.hide
	$scope.addRelation = ->
		$scope.relations.push {
			relation: $scope.relations.length + 1
			cardinality: ''

		}
		$scope.nodes.push {
			op: "scan", l: $scope.relations.length, relations: $scope.relations.length
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

	$scope.getInitalTree = ->
		for n in $scope.nodes
			return n if not n.hide

	$scope.addToConfig = ->
		configFile =
			{
				name: "test"
				relations: $scope.relations,
				joinEdges: $scope.joinEdges,
				algorithms: $scope.algorithms,
				inital_tree: $scope.getInitalTree()
			}
		$scope.configFile.push configFile

