//
//  Rule.h
//
//

#ifndef __RuleBasedOptimizer__Rule__
#define __RuleBasedOptimizer__Rule__

#include <stdio.h>
#include <vector>



template <typename EquivalenceClass, typename PlanNode>
struct Rule
{
    
    
public:
    bool isCommutativityApplicable(PlanNode *);
    PlanNode * commutativity(PlanNode *);
};



template <typename EquivalenceClass, typename PlanNode>
bool Rule<EquivalenceClass, PlanNode>::isCommutativityApplicable(PlanNode * planNode)
{
    return true;
}


template <typename EquivalenceClass, typename PlanNode>
PlanNode * Rule<EquivalenceClass, PlanNode>::commutativity(PlanNode * planNode)
{
    return new PlanNode(planNode->getOperator(), planNode->getRight(), planNode->getLeft());
}




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
struct RightAssociativity
{
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
