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

	$scope.potentialRuelSets = ["RS_B0", "RS_B1", "RS_B2", "GraphRule"]
	$scope.configFile = []

	$scope.nodes = [{op: "scan", l: 1, relations: 1}]
	$scope.toBeJoined = null

	$scope.addRelationByTab = ($event,relation)->
		if(relation == $scope.relations.length)
			$scope.addRelation()

	$scope.removeLastLine = (list)->
		list = list.splice(list.length-1, 1)
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
	$scope.convertToFloat = (value)->
		parseFloat(value)

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
			console.log "NEW"
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
				relations: [],
				joinEdges: [],
				algorithms: $scope.algorithms,
				inital_tree: $scope.getInitalTree()
			}

		for relation in $scope.relations
			configFile.relations.push({
				"id": relation.relation , "cardinality": parseInt(relation.cardinality)
			})

		for edge in $scope.joinEdges
			configFile.joinEdges.push({
				"from": parseInt edge.from
				"to": parseInt edge.to
				"selectivity": parseFloat(edge.selectivity)
			})

		$scope.configFile = []
		$scope.configFile.push configFile

