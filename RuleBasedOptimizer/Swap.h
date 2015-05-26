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
template <typename PlanNode_t, typename Operations_t>
class Swap : public Rule<PlanNode_t, Operations_t>
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
    bool isApplicable(PlanNode_t & aPlanNode) const override
    {
        
        // IF ((A ⨝ B) ⨝ C)
        return aPlanNode.getOperator() == JOIN &&
        aPlanNode.l().getOperator() == JOIN &&
        aPlanNode.r().isOverlapping(aPlanNode.l().r());
    };
    
    bool isApplicable(PlanNode_t & aPlanNode, PlanNode_t & left, PlanNode_t & right) const override
    {
        
        return aPlanNode.getOperator() == JOIN &&
        left.getOperator() == JOIN &&
        aPlanNode.r().isOverlapping(left.r());
    };
    
    /**
     * @brief apply swap
     */
    PlanNode_t * apply(PlanNode_t & aPlanNode) const override
    {
        return apply(aPlanNode, * aPlanNode.l().getFirst(), * aPlanNode.r().getFirst());
    };
    
    PlanNode_t * apply(PlanNode_t & aPlanNode, PlanNode_t & left, PlanNode_t & right)  const override
    {
        return & this->o.joinPN(* this->o.join(left.l(), aPlanNode.r()), left.r());    };
    
};


#endif
