//
//  Configuration.h
//

#ifndef RuleBasedOptimizer_Configuration_h
#define RuleBasedOptimizer_Configuration_h

#include <string>
#include <vector>
#include <unordered_map>

#include "BitvectorSmall.h"
#include "Hasher.h"
#include "json11.hpp"
#include "Operations.h"

template <typename PlanNode_t>
class Configuration
{
	typedef unsigned int u_int;
	typedef typename json11::Json Json;
	typedef Operations<PlanNode_t, unsigned int> Operations_t;
	typedef std::vector<std::string> StringVector_t;
	typedef BitVectorSmall<u_int> Bitvector_t;
	typedef std::unordered_map<Bitvector_t, double, Hasher<Bitvector_t>> BvDoubleMap_t;
	typedef typename PlanNode_t::EquivalenceClass_t EquivalenceClass_t;
	typedef std::unordered_map<Bitvector_t, EquivalenceClass_t *>  RelationsMap_t;
	
public:
	Configuration(Json);
	EquivalenceClass_t * getInitalTree();
	
	
private:
	Operations_t *o = Operations_t::exemplar();
	Json _configuration;
	BvDoubleMap_t _cardinality;
	BvDoubleMap_t _selectivity;
	StringVector_t _algorithms;
	
	
	EquivalenceClass_t *createJoinTree(Json, RelationsMap_t);
	RelationsMap_t getRelations();
};

//
// Implementation
//


template <typename PlanNode_t>
Configuration<PlanNode_t>::Configuration(Json configuration)
{
	_configuration = configuration;
	
	for(json11::Json rel : _configuration["relations"].array_items())
	{
		Bitvector_t b;
		b.set(rel["id"].int_value());
		_cardinality.insert({{b, rel["cardinality"].int_value()}});
	}
	
	for(json11::Json sel : _configuration["joinEdges"].array_items())
	{
		Bitvector_t b;
		b.set(sel["from"].int_value());
		b.set(sel["to"].int_value());
		_cardinality.insert({{b, sel["selectivtity"].number_value()}});
	}
	
	for(json11::Json algo : _configuration["algorithms"].array_items())
	{
		_algorithms.push_back(algo.string_value());
	}
};
template <typename PlanNode_t>
typename Configuration<PlanNode_t>::RelationsMap_t Configuration<PlanNode_t>::getRelations()
{
	RelationsMap_t relations;
	
	for (json11::Json rel : _configuration["relations"].array_items())
	{
		unsigned int relName = rel.int_value();
		relations.insert({{relName, o->rel(relName)}});
	}
	
	for (json11::Json edge : _configuration["joinEdges"].array_items())
	{
		relations.at(edge["from"].int_value())->addNeighbor(edge["to"].int_value());
		relations.at(edge["to"].int_value())->addNeighbor(edge["from"].int_value());
	}
	return relations;
};

template <typename PlanNode_t>
typename Configuration<PlanNode_t>::EquivalenceClass_t * Configuration<PlanNode_t>::createJoinTree(Json query, RelationsMap_t relations)
{
	if (query["op"].string_value() == "scan")
	{
		return o->scan(* relations.at(query["l"].int_value()));
	}
	else
	{
		return o->join( * createJoinTree(query["l"], relations), * createJoinTree(query["r"], relations));
	}
}


template <typename PlanNode_t>
typename Configuration<PlanNode_t>::EquivalenceClass_t * Configuration<PlanNode_t>::getInitalTree()
{
	return createJoinTree(_configuration["query"], getRelations());
};

#endif
