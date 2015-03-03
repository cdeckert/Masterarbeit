//
//  Exchange_B2.h
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 03/03/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
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
	bool isApplicable(PlanNode & aPlanNode) const override
	{
	// IF (A ⨝ (B ⨝ C))
	return aPlanNode.isExchangeEnabled() &&
	aPlanNode.getOperator() == JOIN &&
	aPlanNode.getLeft().getOperator() == JOIN &&
	aPlanNode.getRight().getOperator() == JOIN &&
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

		// (A⨝B) ⨝ (C⨝D)

		auto & a = aPlanNode.getLeft().getLeft();
		auto & b = aPlanNode.getLeft().getRight();
		auto & c = aPlanNode.getRight().getLeft();
		auto & d = aPlanNode.getRight().getRight();

		unsigned int a_pred = aPlanNode.getLeft().getLeftAttribute();
		unsigned int b_pred = aPlanNode.getLeft().getRightAttribute();
		unsigned int c_pred = aPlanNode.getRight().getLeftAttribute();
		unsigned int d_pred = aPlanNode.getRight().getRightAttribute();

		unsigned int main_left = aPlanNode.getLeftAttribute();
		unsigned int main_right = aPlanNode.getRightAttribute();

		PlanNode & p = this->o.joinPN(
							this->o.join(a, d).on(a_pred, d_pred),
							this->o.join(c,b).on(c_pred, b_pred)
							  ).on(main_left, main_right);
		p.disableAllAndEnableCommutativity();
		return & p;



		return NULL;

	};

};



#endif
