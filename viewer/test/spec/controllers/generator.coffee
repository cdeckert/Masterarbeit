'use strict'

describe 'Controller: GeneratorCtrl', ->

  # load the controller's module
  beforeEach module 'viewerApp'

  GeneratorCtrl = {}
  scope = {}

  # Initialize the controller and a mock scope
  beforeEach inject ($controller, $rootScope) ->
    scope = $rootScope.$new()
    GeneratorCtrl = $controller 'GeneratorCtrl', {
      $scope: scope
    }

  it 'should attach a list of awesomeThings to the scope', ->
    expect(scope.awesomeThings.length).toBe 3
