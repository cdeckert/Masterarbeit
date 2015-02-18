//
//  Types.h
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 2/17/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#ifndef RuleBasedOptimizer_Types_h
#define RuleBasedOptimizer_Types_h

#include<stdint.h>

#include "PlanNode.h"
#include "BitvectorSmall.h"
#include "EquivalenceClass.h"

typedef BitVectorSmall<unsigned int> Bitvector32_t;
//typedef Operator<EquivalenceClass_t, Bitvector32_t> Operator_t;
//typedef PlanNode<int, Bitvector32_t> PlanNode_t;

//typedef EquivalenceClass<PlanNode_t, Bitvector32_t> EquivalenceClass_t;

typedef uint32_t uint;
typedef uint64_t uint64;


#endif
