//
//  RightAssociativity.h
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 2/20/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#ifndef RuleBasedOptimizer_RightAssociativity_h
#define RuleBasedOptimizer_RightAssociativity_h

template <typename PlanNode, typename EquivalenceClass>
class RightAssociativity: public Rule<PlanNode>
{
    
public:
    RightAssociativity(){};
    
    PlanNode * apply(PlanNode &) override;
    bool isApplicable(PlanNode &);
};


template <typename PlanNode, typename EquivalenceClass>
bool RightAssociativity<PlanNode,EquivalenceClass>::isApplicable(PlanNode & aPlanNode) {
    return aPlanNode.hasRightEC();
}

template <typename PlanNode, typename EquivalenceClass>
PlanNode * RightAssociativity<PlanNode, EquivalenceClass>::apply(PlanNode & aPlanNode)
{
    
    
    
    EquivalenceClass * newLeft = new EquivalenceClass();
    
    if(aPlanNode.getRightEC().node().hasLeftEC())
    {
        if(aPlanNode.hasLeftEC())
        {
            PlanNode * newLeftPlan = new PlanNode(JOIN, aPlanNode.getLeftEC(), aPlanNode.getRightEC().node().getLeftEC());
            newLeft->push_back(*newLeftPlan);
        }
        else
        {
            PlanNode * newLeftPlan = new PlanNode(JOIN, aPlanNode.getLeft(), aPlanNode.getRightEC().node().getLeftEC());
            newLeft->push_back(*newLeftPlan);
        }
    }
    else{
        if(aPlanNode.hasLeftEC())
        {
            PlanNode * newLeftPlan = new PlanNode(JOIN, aPlanNode.getLeftEC(), aPlanNode.getRightEC().node().getLeft());
            newLeft->push_back(*newLeftPlan);
        }
        else
        {
            PlanNode * newLeftPlan = new PlanNode(JOIN, aPlanNode.getLeft(), aPlanNode.getRightEC().node().getLeft());
            newLeft->push_back(*newLeftPlan);
        }
    }
    
    
    if(aPlanNode.hasLeftEC())
    {
        return new PlanNode(JOIN, aPlanNode.getLeftEC(), *newLeft);
    }
    else
    {
        return new PlanNode(JOIN, aPlanNode.getLeft(), *newLeft);
    }
    return  &aPlanNode; //new PlanNode(JOIN, aPlanNode.getRight(), aPlanNode.getLeft());
}

#endif
