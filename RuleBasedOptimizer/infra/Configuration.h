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

struct Configuration
{
	typedef unsigned int u_int;
	typedef std::vector<std::string> StringVector_t;
	typedef BitVectorSmall<u_int> Bitvector_t;
	typedef std::unordered_map<Bitvector_t, double, Hasher<Bitvector_t>> BvDoubleMap_t;
	struct TestAlgorithm
	{
		std::string _name;
		std::string _ruleset;
	};
	
	
	
	
	typedef std::vector<TestAlgorithm> AlgorithmVector_t;
public:
	BvDoubleMap_t _cardinality;
	BvDoubleMap_t _selectivity;
	AlgorithmVector_t _algorithms;
	
private:
};

#endif
