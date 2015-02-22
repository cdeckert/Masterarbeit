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
class CommutativityRule: public Rule<PlanNode>
{
    
public:
    CommutativityRule(){};
    
    PlanNode * apply(PlanNode &) override;
    void whatever(){
        
    };
};


template <typename PlanNode>
PlanNode * CommutativityRule<PlanNode>::apply(PlanNode & aPlanNode)
{
    
    return new PlanNode(JOIN, aPlanNode.getRight(),  aPlanNode.getLeft());
}



#endif
