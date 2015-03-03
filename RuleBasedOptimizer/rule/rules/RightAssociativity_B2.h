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
class RightAssociativity_B2 : public Rule<PlanNode, Operations_t>
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
	bool isApplicable(PlanNode & aPlanNode) const override
	{
	// IF (A ⨝ (B ⨝ C))
	return aPlanNode.getOperator() == JOIN &&
	aPlanNode.getRight().begin()->getOperator() == JOIN &&
	aPlanNode.getLeftAttribute() == aPlanNode.getLeft().getLeftAttribute();
};

/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param aPlanNode [description]
 * @return [description]
 */
PlanNode * apply(PlanNode & aPlanNode) const override
{

auto & a = aPlanNode.getLeft().getLeft();
unsigned int a_joinP = aPlanNode.getLeftAttribute();

auto & b = aPlanNode.getRight().getLeft();
unsigned int b_joinP = aPlanNode.getRight().getLeftAttribute();

auto & c = aPlanNode.getRight().getRight();
unsigned int c_joinP = aPlanNode.getRight().getRightAttribute();



return & this->o.joinPN(
						this->o.join(a, b).on(a_joinP, b_joinP), c
						).on(b_joinP, c_joinP);

};

};




#endif
