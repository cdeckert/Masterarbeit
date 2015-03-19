//
//  Commutativity_B2.h
//

#ifndef RuleBasedOptimizer_Commutativity_B2_h
#define RuleBasedOptimizer_Commutativity_B2_h

#include "Rule.h"

/**
 * @brief Commutativity
 * @details Rule that creates commutative plan nodes based on a given node
 *
 * @tparam PlanNode_t PlanNode
 * @tparam Operations_t basic operations like join and scan
 */
template <typename PlanNode_t, typename Operations_t>
class CommutativityRule_B2 : public Rule<PlanNode_t, Operations_t>
{
public:
    
    /**
     * @brief checks whether or not commutativity is applicable
     * @details Commutativity is applicable in case the given operation is "JOIN"
     *
     * @param aPlanNode a given plan node
     * @return true in case the rule is applicable
     */
	bool isApplicable(PlanNode_t & aPlanNode) const override;


    /**
     * @brief applies the commutativity rule
     * @details Applies the commutativity rule:
     * (A ⨝ B) becomes (B ⨝ A)
     *
     * @param aPlanNode a given plan node
     * @return a new plan node, which is logical equal to the given plan node
    */
    PlanNode_t * apply(PlanNode_t & aPlanNode) const override;
};

template <typename PlanNode_t, typename Operations_t>
bool CommutativityRule_B2<PlanNode_t, Operations_t>::isApplicable(PlanNode_t & aPlanNode) const
{
	return aPlanNode.isCommutativityEnabled() && aPlanNode.getOperator() != SCAN;
};

template <typename PlanNode_t, typename Operations_t>
PlanNode_t * CommutativityRule_B2<PlanNode_t, Operations_t>::apply(PlanNode_t & aPlanNode) const
{
	PlanNode_t & p = this->o.joinPN(aPlanNode.getRight(), aPlanNode.getLeft()).
	on(aPlanNode.getRightAttribute(), aPlanNode.getLeftAttribute());
	p.disableAllRules();
	return &p;
};



#endif
