//
//  LeftAssociativity.h
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 16/02/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#ifndef RuleBasedOptimizer_LeftAssociativity_h
#define RuleBasedOptimizer_LeftAssociativity_h


template <typename PlanNode, typename EquivalenceClass, typename Descendant>
class LeftAssociativity: public Rule<PlanNode>
{
public:
    LeftAssociativity(){};
    
    PlanNode * apply(PlanNode &) override;
    bool isApplicable(PlanNode &);
};


template <typename PlanNode, typename EquivalenceClass, typename Descendant>
bool LeftAssociativity<PlanNode,EquivalenceClass, Descendant>::isApplicable(PlanNode & aPlanNode) {
    return !aPlanNode.getLeft().isLeaf();
}

template <typename PlanNode, typename EquivalenceClass, typename Descendant>
PlanNode * LeftAssociativity<PlanNode, EquivalenceClass, Descendant>::apply(PlanNode & aPlanNode)
{
    std::cout <<  aPlanNode.str() << std::endl;
    std::cout.flush();
    EquivalenceClass * newRight = new EquivalenceClass();
    PlanNode * rightNode = new PlanNode(JOIN, aPlanNode.getLeft().getRight(), aPlanNode.getRight());
    
    std::cout << "rightNode.str()" << rightNode->str() << std::endl;
    std::cout.flush();
    newRight->push_back(*rightNode);
    
    
    return new PlanNode(JOIN, aPlanNode.getLeft().getLeft(), *new Descendant(newRight));

}


#endif
