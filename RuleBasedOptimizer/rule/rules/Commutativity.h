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


template <typename PlanNode, typename Operations_t>
class CommutativityRule : public Rule<PlanNode, Operations_t>
{
public:
    
    /**
     * @brief checks whether or not commutativity is applicable
     */
    bool isApplicable(PlanNode & aPlanNode) const override
    {
        return aPlanNode.getOperator() != SCAN;
    }
    
    /**
     * @brief apply commutativity
     */
    PlanNode * apply(PlanNode & aPlanNode) const override
    {
        return this->o.joinPN(aPlanNode.getRight(), aPlanNode.getLeft());
    }
};



#endif
