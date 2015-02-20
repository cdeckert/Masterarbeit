//
//  LeftAssociativity.h
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 16/02/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#ifndef RuleBasedOptimizer_LeftAssociativity_h
#define RuleBasedOptimizer_LeftAssociativity_h


template <typename PlanNode, typename EquivalenceClass>
class LeftAssociativity: public Rule<PlanNode>
{
    
public:
    LeftAssociativity(){};
    
    PlanNode * apply(PlanNode &) override;
    bool isApplicable(PlanNode &);
};


template <typename PlanNode, typename EquivalenceClass>
bool LeftAssociativity<PlanNode,EquivalenceClass>::isApplicable(PlanNode & aPlanNode) {
    return aPlanNode.hasLeftEC();
}

template <typename PlanNode, typename EquivalenceClass>
PlanNode * LeftAssociativity<PlanNode, EquivalenceClass>::apply(PlanNode & aPlanNode)
{
    
    
    aPlanNode.getLeftEC().node().getLeftEC();
    //PlanNode && leftNode = aPlanNode.getLeftEC().;
    
    EquivalenceClass * newRight = new EquivalenceClass();
    
    if(aPlanNode.getLeftEC().node().hasRightEC())
    {
        if(aPlanNode.hasRightEC())
        {
            PlanNode * newRightPlan = new PlanNode(JOIN, aPlanNode.getLeftEC().node().getRightEC(), aPlanNode.getRightEC());
            newRight->push_back(*newRightPlan);
        }
        else
        {
            PlanNode * newRightPlan = new PlanNode(JOIN, aPlanNode.getLeftEC().node().getRight(), aPlanNode.getRightEC());
            newRight->push_back(*newRightPlan);
        }
    }
    else
    {
        if(aPlanNode.hasRightEC())
        {
            PlanNode * newRightPlan = new PlanNode(JOIN, aPlanNode.getLeftEC().node().getRightEC(), aPlanNode.getRight());
            newRight->push_back(*newRightPlan);
        }
        else
        {
            PlanNode * newRightPlan = new PlanNode(JOIN, aPlanNode.getLeftEC().node().getRight(), aPlanNode.getRight());
            newRight->push_back(*newRightPlan);
        }
    }
    
    if(aPlanNode.getLeftEC().node().hasLeftEC())
    {
        return new PlanNode(JOIN,  aPlanNode.getLeftEC().node().getLeftEC(), *newRight);
    }
    else
    {
        return new PlanNode(JOIN,  aPlanNode.getLeftEC().node().getLeft(), *newRight);
    }
    
    return  &aPlanNode; //new PlanNode(JOIN, aPlanNode.getRight(), aPlanNode.getLeft());
}


#endif
