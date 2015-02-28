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
#include "ExhaustiveTransformation.h"
#include "BasicRuleSet.h"
#include "RS_B0.h"
#include "Operations.h"


typedef unsigned int u_int;
typedef BitVectorSmall<u_int> Bitvector_t;
typedef PlanNode<Bitvector_t> PlanNode_t;
typedef EquivalenceClass<Bitvector_t, PlanNode_t> EquivalenceClass_t;
typedef EquivalenceClassIterator<Bitvector_t, PlanNode_t> EquivalenceClassIterator_t;
typedef Operations<Bitvector_t, EquivalenceClass_t, PlanNode_t, u_int> Operations_t;
typedef Rule<PlanNode_t, Operations_t> Rule_t;
typedef RS_B0<Rule_t, PlanNode_t, Operations_t> RS_B0_t;

typedef ExhaustiveTransformation<EquivalenceClass_t, EquivalenceClassIterator_t, PlanNode_t, Bitvector_t, Operations_t, Rule_t> ExhaustiveTransformation_t;






#endif
