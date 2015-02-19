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
    
    if(aPlanNode.hasLeftEC())
    {
        if(aPlanNode.hasRightEC())
        {
            
            return PlanNode(JOIN, aPlanNode.getRightEC(),  aPlanNode.getLeftEC());
        }
        else
        {
            return PlanNode(JOIN, aPlanNode.getRight(), aPlanNode.getLeftEC());
        }
    }
    else
    {
        if(aPlanNode.hasRightEC())
        {
            return PlanNode(JOIN, aPlanNode.getRightEC(), aPlanNode.getLeft());
        }
        else
        {
            return PlanNode(JOIN, aPlanNode.getRight(), aPlanNode.getLeft());
        }
    }
}



#endif
