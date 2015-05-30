//
//  LeftAssociativity_B2.h
//

#ifndef RuleBasedOptimizer_LeftAssociativity_B2_h
#define RuleBasedOptimizer_LeftAssociativity_B2_h


/**
 * @brief Left Associativity
 * @details Rule that creates commutative plan nodes based on a given node
 *
 * @tparam PlanNode_t PlanNode
 * @tparam Operations_t basic operations like join and scan
 */
template <typename PlanNode_t, typename Operations_t>
class LeftAssociativity_B2 : public LeftAssociativity<PlanNode_t, Operations_t>
{

	typedef LeftAssociativity<PlanNode_t, Operations_t> Parent_t;
public:
	/**
	 * @brief checks whether or not left associativity is applicable
	 * @details left associativity is applicable in case the given operation is
	 * "JOIN" the left descendant node is a join
	 *
	 * @param aPlanNode a given plan node
	 * @return true in case the rule is applicable
	 */
	bool isApplicable(PlanNode_t &aPlanNode) const override
	{
		// IF ((A ⨝ B) ⨝ C)
		return aPlanNode.isLeftAssociativityEnabled() && Parent_t::isApplicable(aPlanNode);
	};
	
	bool isApplicable(PlanNode_t & aPlanNode, PlanNode_t & left, PlanNode_t & right) const override
	{
		// IF ((A ⨝ B) ⨝ C)
		return aPlanNode.isLeftAssociativityEnabled() && Parent_t::isApplicable(aPlanNode, left, right);
	};

	/**
	 * @brief apply left associativity
	 */
	PlanNode_t *apply(PlanNode_t &aPlanNode) const override
	{
		return Parent_t::apply(aPlanNode)->disableAllAndEnableCommutativity();
	};
	
	
	PlanNode_t *apply(PlanNode_t & aPlanNode, PlanNode_t & left, PlanNode_t & right) const override
	{
		return Parent_t::apply(aPlanNode, left, right)->disableAllAndEnableCommutativity();
	};
	
	std::string getName()  const override { return "LeftAssociativity_B2"; };

};



#endif
