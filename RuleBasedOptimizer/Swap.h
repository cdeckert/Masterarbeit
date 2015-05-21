//
//  Swap.h
//

#ifndef RuleBasedOptimizer_Swap_h
#define RuleBasedOptimizer_Swap_h


/**
 * @brief Swap
 * @details Rule that creates swaped plan nodes based on a given node
 *
 * @tparam PlanNode_t PlanNode
 * @tparam Operations_t basic operations like join and scan
 */
template <typename PlanNode, typename Operations_t>
class Swap : public Rule<PlanNode, Operations_t>
{
    
    
public:
    /**
     * @brief checks whether or not swap is applicable
     * @details swap is applicable in case the given operation is
     * "JOIN" the left descendant node is a join
     *
     * @param aPlanNode a given plan node
     * @return true in case the rule is applicable
     */
    bool isApplicable(PlanNode & aPlanNode) const override
    {
        
        // IF ((A ⨝ B) ⨝ C)
        return aPlanNode.getOperator() == JOIN &&
        aPlanNode.l().getOperator() == JOIN &&
        aPlanNode.r().isOverlapping(aPlanNode.l().r());
    };
    
    /**
     * @brief apply left associativity
     */
    PlanNode * apply(PlanNode & aPlanNode) const override
    {
        return & this->o.joinPN(* this->o.join(aPlanNode.l().l(), aPlanNode.r()), aPlanNode.l().r());
        return & this->o.joinPN(aPlanNode.l().l(), *this->o.join(aPlanNode.l().r(), aPlanNode.r()));
    };
    
};


#endif
