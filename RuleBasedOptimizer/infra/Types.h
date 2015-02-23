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

typedef unsigned int u_int;
typedef BitVectorSmall<u_int> Bitvector_t;
typedef PlanNode<Bitvector_t> PlanNode_t;
typedef EquivalenceClass<Bitvector_t, PlanNode_t> EquivalenceClass_t;

#endif
