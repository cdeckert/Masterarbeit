//
//  LeftAssociativity.h
//

#ifndef RuleBasedOptimizer_LeftAssociativity_h
#define RuleBasedOptimizer_LeftAssociativity_h

/**
 * @brief Left Associativity
 * @details Rule that creates commutative plan nodes based on a given node
 *
 * @tparam PlanNode_t PlanNode
 * @tparam Operations_t basic operations like join and scan
 */
template <typename PlanNode, typename Operations_t>
class LeftAssociativity : public Rule<PlanNode, Operations_t>
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

		joinPN(aPlanNode.l().l(), join(aPlanNode.l().r(), aPlanNode.r(), neighborhood);
		return &aPlanNode;
	};

};


#endif
