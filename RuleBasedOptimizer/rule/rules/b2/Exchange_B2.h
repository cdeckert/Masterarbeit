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
template <typename PlanNode, typename Operations_t>
class Exchange_B2 : public Rule<PlanNode, Operations_t>
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
	bool isApplicable(PlanNode &aPlanNode) const override
	{
		// IF (A ⨝ B) ⨝ (C ⨝ D) <-> (A ⨝ D) ⨝ (C ⨝ B)
		return aPlanNode.isExchangeEnabled() &&
			   aPlanNode.getOperator() == JOIN &&
			   aPlanNode.l().getOperator() == JOIN &&
			   aPlanNode.r().getOperator() == JOIN &&
			   aPlanNode.l().r().isOverlapping(aPlanNode.r().r());
	};

	/**
	 * @brief [brief description]
	 * @details [long description]
	 *
	 * @param aPlanNode [description]
	 * @return [description]
	 */
	PlanNode *apply(PlanNode &aPlanNode) const override
	{
		PlanNode &pn = this->o.joinPN(* this->o.join(aPlanNode.l().l(),  aPlanNode.r().r()), * this->o.join(aPlanNode.r().l(), aPlanNode.l().r()));
		pn.disableAllAndEnableCommutativity();
		return & pn;
	};

};




#endif
