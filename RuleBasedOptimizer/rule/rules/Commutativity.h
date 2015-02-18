//
//  Commutativity.h
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 12/02/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#ifndef RuleBasedOptimizer_Commutativity_h
#define RuleBasedOptimizer_Commutativity_h

#include "Rule.h"

template <typename PlanNode>
class Commutativity: public Rule<PlanNode>
{
    
public:
    Commutativity(){};
    
    PlanNode apply(const PlanNode &) override;
};


template <typename PlanNode>
PlanNode Commutativity<PlanNode>::apply(const PlanNode & aPlanNode)
{
    return  PlanNode(aPlanNode.getOperator(), aPlanNode.getRight(), aPlanNode.getLeft());
}



#endif