//
//  LeftAssociativity.h
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 16/02/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#ifndef RuleBasedOptimizer_LeftAssociativity_h
#define RuleBasedOptimizer_LeftAssociativity_h


template <typename PlanNode>
class LeftAssociativity: public Rule<PlanNode>
{
    
public:
    LeftAssociativity(){};
    
    PlanNode * apply(PlanNode &) override;
};


template <typename PlanNode>
PlanNode * LeftAssociativity<PlanNode>::apply(PlanNode & aPlanNode)
{
    return  new PlanNode(JOIN, aPlanNode.getRight(), aPlanNode.getLeft());
}


#endif
