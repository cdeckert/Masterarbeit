//
//  LeftAssociativity.h
//

#ifndef RuleBasedOptimizer_LeftAssociativity_h
#define RuleBasedOptimizer_LeftAssociativity_h


template <typename PlanNode, typename Operations_t>
class LeftAssociativity : public Rule<PlanNode, Operations_t>
{
    
    
public:
    /**
     * @brief checks whether or not leftAssociativity is applicable
     */
    bool isApplicable(PlanNode & aPlanNode) const override
    {
        // IF ((A ⨝ B) ⨝ C)
        return aPlanNode.getOperator() == JOIN && aPlanNode.getLeft().getOperator() == JOIN &&
        aPlanNode.getRightAttribute() == aPlanNode.getLeft().getLeftAttribute();
    };

    /**
     * @brief apply left associativity
     */
    PlanNode * apply(PlanNode & aPlanNode) const override
    {
        // join(join(a, b).on(a.1, b.1), c).on(b.1, c.1) => join(a, join(b,c).on(b.1, c.1)).on(a.1, b.1)
        auto & a = aPlanNode.getLeft().getLeft();
        unsigned int a_joinP = aPlanNode.getLeft().getLeftAttribute();

        auto & b = aPlanNode.getLeft().getRight();
        unsigned int b_joinP = aPlanNode.getLeft().getRightAttribute();

        auto & c = aPlanNode.getRight();
        unsigned int c_joinP = aPlanNode.getRightAttribute();

        return & this->o.joinPN(
            a, this->o.join(b,c).on(b_joinP, c_joinP)
        ).on(a_joinP, b_joinP);
    };

};


#endif
