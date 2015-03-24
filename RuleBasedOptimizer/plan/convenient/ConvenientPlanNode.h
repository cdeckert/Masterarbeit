//
//  ConvenientPlanNode.h
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 24/03/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#ifndef RuleBasedOptimizer_ConvenientPlanNode_h
#define RuleBasedOptimizer_ConvenientPlanNode_h


#include "PlanNode.h"

template <typename Bitvector>
class ConvenientPlanNode : public PlanNode<Bitvector>
{
public:
	ConvenientPlanNode() : PlanNode();
};


#endif
