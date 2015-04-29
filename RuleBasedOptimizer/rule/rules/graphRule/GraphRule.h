//
//  GraphRule.h
//

#ifndef RuleBasedOptimizer_GraphRule_h
#define RuleBasedOptimizer_GraphRule_h


/**
 * @brief Graph Rule
 * @details Rule that creates commutative plan nodes based on a given node
 *
 * @tparam PlanNode_t PlanNode
 * @tparam Operations_t basic operations like join and scan
 */
template <typename PlanNode, typename Operations_t>
class GraphRule : public Rule<PlanNode, Operations_t>
{
    
    
public:
    /**
     * @brief checks whether or not left associativity is applicable
     * @details left associativity is applicable in case the given operation is
     * "JOIN" the left descendant node is a join
     *
     * @param aPlanNode a given plan node
     * @return true in case the rule is applicable
     */
    bool isApplicable(PlanNode & aPlanNode) const override
    {
        // IF is Parent Node
        return aPlanNode.getOperator() == JOIN;
    };
    
    /**
     * @brief apply left associativity
     */
    PlanNode * apply(PlanNode & aPlanNode) const override
    {
        //return & this->o.joinPN(aPlanNode.l().l(), *this->o.join(aPlanNode.l().r(), aPlanNode.r()));
        return NULL;
    };
    
};




#endif
