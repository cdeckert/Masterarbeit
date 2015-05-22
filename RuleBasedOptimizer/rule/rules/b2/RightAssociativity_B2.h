//
//  RightAssociativity_B2.h
//

#ifndef RuleBasedOptimizer_RightAssociativity_B2_h
#define RuleBasedOptimizer_RightAssociativity_B2_h

/**
 * @brief Right associativity
 * @details Rule that creates commutative plan nodes based on a given node
 *
 * @tparam PlanNode_t PlanNode
 * @tparam Operations_t basic operations like join and scan
 */
template <typename PlanNode, typename Operations_t>
class RightAssociativity_B2 : public RightAssociativity<PlanNode, Operations_t>
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
		// IF (A ⨝ (B ⨝ C))
		return aPlanNode.isRightAssociativityEnabled() &&
			   aPlanNode.getOperator() == JOIN &&
			   aPlanNode.r().getOperator() == JOIN &&
			   aPlanNode.l().isOverlapping(aPlanNode.r().l());
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
		return this->o.joinPN(*this->o.join(aPlanNode.l(), aPlanNode.r().l()), aPlanNode.r().r()).disableAllAndEnableCommutativity();
	};

};




#endif
