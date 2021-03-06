//
//  Commutativity.h
//

#ifndef RuleBasedOptimizer_Commutativity_h
#define RuleBasedOptimizer_Commutativity_h

//#include "Rule.h"

/**
 * @brief Commutativity
 * @details Rule that creates commutative plan nodes based on a given node
 *
 * @tparam PlanNode_t PlanNode
 * @tparam Operations_t basic operations like join and scan
 */
template <typename PlanNode_t, typename Operations_t>
class CommutativityRule : public Rule<PlanNode_t, Operations_t>
{
    typedef typename PlanNode_t::EquivalenceClass_t EquivalenceClass_t;
public:
	
	/**
	 * @brief checks whether or not commutativity is applicable
	 * @details Commutativity is applicable in case the given operation is JOIN
	 *
	 * @param aPlanNode a given plan node
	 * @return true in case the rule is applicable
	 */
	bool isApplicable(PlanNode_t & aPlanNode) const override
	{
		return aPlanNode.hasRight() && isApplicable(aPlanNode, * aPlanNode.l().getFirst(), * aPlanNode.r().getFirst());
	}
    bool isApplicable(PlanNode_t & aPlanNode, PlanNode_t & left, PlanNode_t & right) const override
    {
        
        return aPlanNode.getOperator() != SCAN && aPlanNode.l().isOverlapping(aPlanNode.r());
    }


	/**
	 * @brief applies the commutativity rule
	 * @details Applies the commutativity rule:
	 * (A ⨝ B) becomes (B ⨝ A)
	 *
	 * @param aPlanNode a given plan node
	 * @return a new plan node, which is logical equal to the given plan node
	 */
	PlanNode_t * apply(PlanNode_t & aPlanNode) const override
	{
    
		return apply(aPlanNode,* aPlanNode.r().getFirst(),* aPlanNode.l().getFirst());
	};
    
    PlanNode_t * apply(PlanNode_t & aPlanNode, PlanNode_t & left, PlanNode_t & right)  const override
    {
        return & this->o.joinPN(aPlanNode.r(), aPlanNode.l());
    }
    
    std::string getName()  const override { return "Commutativity"; };
};



#endif
