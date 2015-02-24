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
    CommutativityRule(Reservoir<PlanNode> * planNodes)
    {
        _planNodes = planNodes;
    };
    
    PlanNode * apply(PlanNode &) override;
    bool isApplicable(PlanNode & aPlanNode)
    {
        return aPlanNode.getOperator() != SCAN;
    }
    
private:
    Reservoir<PlanNode> * _planNodes;
};


template <typename PlanNode>
PlanNode * CommutativityRule<PlanNode>::apply(PlanNode & aPlanNode)
{
    PlanNode * p = _planNodes->get_new_entry();
    p->set(aPlanNode.getOperator(), *aPlanNode.getRight(), *aPlanNode.getLeft());
    return p;
}



#endif
