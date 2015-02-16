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
    
    PlanNode apply(const PlanNode &) override;
};


template <typename PlanNode>
PlanNode LeftAssociativity<PlanNode>::apply(const PlanNode & aPlanNode)
{
    return  PlanNode(aPlanNode.getOperator(), aPlanNode.getRight(), aPlanNode.getLeft());
}


#endif
