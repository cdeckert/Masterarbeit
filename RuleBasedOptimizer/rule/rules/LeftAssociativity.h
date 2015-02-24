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
    return aPlanNode.getOperator() == JOIN && aPlanNode.getLeft()->begin().node().getOperator() == JOIN;
}

template <typename PlanNode, typename EquivalenceClass>
PlanNode * LeftAssociativity<PlanNode, EquivalenceClass>::apply(PlanNode & aPlanNode)
{
    
    PlanNode * p = new PlanNode();
    p->set(JOIN, *aPlanNode.getLeft()->begin().node().getRight(), *aPlanNode.getRight());
    EquivalenceClass *eq = new EquivalenceClass();
    eq->push_back(*p);
    
    PlanNode *resultP = new PlanNode();
    resultP->set(JOIN, *aPlanNode.getLeft()->begin().node().getLeft(), *eq);
    return resultP;

}


#endif
