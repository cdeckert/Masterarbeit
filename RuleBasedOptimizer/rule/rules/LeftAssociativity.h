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
        return aPlanNode.getOperator() == JOIN && aPlanNode.getLeft()->begin()->getOperator() == JOIN;
    };

    /**
     * @brief apply left associativity
     */
    PlanNode * apply(PlanNode & aPlanNode) const override
    {
        return this->o.joinPN(
                                 aPlanNode.getLeft()->begin()->getLeft(),
                                 this->o.join(aPlanNode.getLeft()->begin()->getRight(), aPlanNode.getRight())
                                 );
    
    
    };

};


#endif
