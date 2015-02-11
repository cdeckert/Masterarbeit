//
//  Rule.h
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 04/02/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#ifndef __RuleBasedOptimizer__Rule__
#define __RuleBasedOptimizer__Rule__

#include <stdio.h>
#include <vector>





template <class Plan>
struct Commutativity
{
public:
    bool isApplicable(Plan* plan)
    {
        return plan->hasLeft() && plan->hasRight();
    }
    Plan apply(Plan* plan)
    {
        if(isApplicable(plan))
        {
            Plan newPlan = new Plan(plan->right, plan->left);
            return &newPlan;
        }
        return NULL;
    }
};

template <class Plan>
struct RightAssociativity {
public:
    bool isApplicable(Plan* plan)
    {
        return plan->hasLeft() && plan->hasRight() && plan->getRight()->hasLeft();
    }
    Plan apply(Plan * plan)
    {
        Plan newPlan = new Plan(new Plan(plan->getLeft(), plan->getRight()->getLeft()), plan->getRight()->getRight());
        return newPlan;
    }
};


#endif /* defined(__RuleBasedOptimizer__Rule__) */
