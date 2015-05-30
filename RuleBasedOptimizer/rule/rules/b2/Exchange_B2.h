//
//  Exchange_B2.h
//

#ifndef RuleBasedOptimizer_Exchange_B2_h
#define RuleBasedOptimizer_Exchange_B2_h


/**
 * @brief Right associativity
 * @details Rule that creates commutative plan nodes based on a given node
 *
 * @tparam PlanNode_t PlanNode
 * @tparam Operations_t basic operations like join and scan
 */
template <typename PlanNode_t, typename Operations_t>
class Exchange_B2 : public Rule<PlanNode_t, Operations_t>
{


public:
	/**
	 * @brief checks whether or not right associativity is applicable
	 * @details right associativity is applicable in case the given operation
	 * is "JOIN" the left descendant node is a join
	 *
	 * @param aPlanNode a given plan node
	 * @return true in case the rule is applicable
	 */
	bool isApplicable(PlanNode_t &aPlanNode) const override
	{
		// IF (A ⨝ B) ⨝ (C ⨝ D) <-> (A ⨝ D) ⨝ (C ⨝ B)
        return aPlanNode.getOperator() == JOIN &&
        isApplicable(aPlanNode, * aPlanNode.l().getFirst(), * aPlanNode.r().getFirst());
	};
    
    bool isApplicable(PlanNode_t & aPlanNode, PlanNode_t & left, PlanNode_t & right) const override
    {
        return aPlanNode.isExchangeEnabled() &&
        aPlanNode.getOperator() == JOIN &&
        left.getOperator() == JOIN &&
        right.getOperator() == JOIN &&
        left.r().isOverlapping(right.r());
    };

	/**
	 * @brief [brief description]
	 * @details [long description]
	 *
	 * @param aPlanNode [description]
	 * @return [description]
	 */
	PlanNode_t *apply(PlanNode_t &aPlanNode) const override
	{
		return apply(aPlanNode, * aPlanNode.l().getFirst(), * aPlanNode.r().getFirst());
	};
    
    PlanNode_t * apply(PlanNode_t & aPlanNode, PlanNode_t & left, PlanNode_t & right)  const override
    {
        PlanNode_t &pn = this->o.joinPN(* this->o.join(left.l(),  right.r()), * this->o.join(right.l(), left.r()));
        pn.disableAllAndEnableCommutativity();
        return & pn;
    };
    
    std::string getName()  const override { return "Exchange_B2"; };

};




#endif
