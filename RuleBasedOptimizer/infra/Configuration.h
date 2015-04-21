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

template <typename PlanNode_t>
struct Configuration
{
	typedef unsigned int u_int;
	typedef typename json11::Json Json;
	typedef std::vector<std::string> StringVector_t;
	typedef BitVectorSmall<u_int> Bitvector_t;
	typedef std::unordered_map<Bitvector_t, double, Hasher<Bitvector_t>> BvDoubleMap_t;
	typedef typename PlanNode_t::EquivalenceClass_t EquivalenceClass_t;
	
public:
	BvDoubleMap_t _cardinality;
	BvDoubleMap_t _selectivity;
	StringVector_t _algorithms;
	EquivalenceClass_t * getInitalTree();
	
private:
	Json initalTree;
};


template <typename PlanNode_t>
EquivalenceClass_t * getInitalTree()
{
	EquivalenceClass_t * e = new EquivalenceClass_t();
	
	return e;
}

#endif
