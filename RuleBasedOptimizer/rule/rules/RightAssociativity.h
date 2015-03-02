//
//  RightAssociativity.h
//  RuleBasedOptimizer
//

#ifndef RuleBasedOptimizer_RightAssociativity_h
#define RuleBasedOptimizer_RightAssociativity_h

template <typename PlanNode, typename Operations_t>
class RightAssociativity : public Rule<PlanNode, Operations_t>
{
    
    
public:
    /**
     * @brief checks whether or not leftAssociativity is applicable
     */
    bool isApplicable(PlanNode & aPlanNode) const override
    {
    // IF (A ⨝ (B ⨝ C))
    return aPlanNode.getOperator() == JOIN && aPlanNode.getRight().begin()->getOperator() == JOIN &&
    aPlanNode.getLeftAttribute() == aPlanNode.getLeft().begin()->getLeftAttribute();
};

/**
 * @brief apply left associativity
 */
PlanNode * apply(PlanNode & aPlanNode) const override
{

    auto & a = aPlanNode.getLeft().begin()->getLeft();
    unsigned int a_joinP = aPlanNode.getLeftAttribute();

    auto & b = aPlanNode.getRight().begin()->getLeft();
    unsigned int b_joinP = aPlanNode.getRight().begin()->getLeftAttribute();

    auto & c = aPlanNode.getRight().begin()->getRight();
    unsigned int c_joinP = aPlanNode.getRight().begin()->getRightAttribute();



    return & this->o.joinPN(
        this->o.join(a, b).on(a_joinP, b_joinP), c
    ).on(b_joinP, c_joinP);

};

};


#endif
