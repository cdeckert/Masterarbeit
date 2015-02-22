//
//  RightAssociativity.h
//  RuleBasedOptimizer
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
    return !aPlanNode.getRight().isLeaf();
}

template <typename PlanNode, typename EquivalenceClass>
PlanNode * RightAssociativity<PlanNode, EquivalenceClass>::apply(PlanNode & aPlanNode)
{
    EquivalenceClass * newLeft = new EquivalenceClass();
    PlanNode * leftNode = new PlanNode(JOIN, aPlanNode.getLeft(), aPlanNode.getRight().getLeft());
    newLeft->push_back(*leftNode);
    
    
    return new PlanNode(JOIN, PlanNode::getDescendant(*newLeft), aPlanNode.getLeft().getRight().getRight());
}

#endif
