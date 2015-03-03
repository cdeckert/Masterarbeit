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
		aPlanNode.getLeft().getOperator() == JOIN &&
		aPlanNode.getRightAttribute() == aPlanNode.getLeft().getLeftAttribute();
	};

	/**
	 * @brief apply left associativity
	 */
	PlanNode * apply(PlanNode & aPlanNode) const override
	{
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
