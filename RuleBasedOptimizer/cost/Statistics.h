//
//  Statistics.h
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 07/04/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#ifndef RuleBasedOptimizer_Statistics_h
#define RuleBasedOptimizer_Statistics_h

#include "Hasher.h"

template <typename Bitvector_t>
class Statistics
{
	std::unordered_map<Bitvector_t, double, Hasher<Bitvector_t>> _cardinality;
	std::unordered_map<Bitvector_t, double, Hasher<Bitvector_t>> _selectivity;
	
public:
	Statistics(){};
	
	double calcCost(Bitvector_t rel1, Bitvector_t rel2){
		return _cardinality.at(rel1) * _cardinality.at(rel2) * _selectivity.at(rel1+rel2);
	}
	
	double getSelectivity(Bitvector_t rel1, Bitvector_t rel2)
	{
		return 1;
	}
};

#endif
