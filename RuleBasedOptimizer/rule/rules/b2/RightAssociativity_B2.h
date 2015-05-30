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
template <typename PlanNode_t, typename Operations_t>
class RightAssociativity_B2 : public RightAssociativity<PlanNode_t, Operations_t>
{

    typedef RightAssociativity<PlanNode_t, Operations_t> Parent_t;
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
		// IF (A ⨝ (B ⨝ C))
		return aPlanNode.isRightAssociativityEnabled() &&
			   aPlanNode.getOperator() == JOIN &&
			   aPlanNode.r().getOperator() == JOIN &&
			   aPlanNode.l().isOverlapping(aPlanNode.r().l());
	};
    
    bool isApplicable(PlanNode_t & aPlanNode, PlanNode_t & left, PlanNode_t & right) const override
    {
        // IF ((A ⨝ B) ⨝ C)
        return aPlanNode.isRightAssociativityEnabled() && Parent_t::isApplicable(aPlanNode, left, right);
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
        return Parent_t::apply(aPlanNode)->disableAllAndEnableCommutativity();
	};
    
    PlanNode_t *apply(PlanNode_t & aPlanNode, PlanNode_t & left, PlanNode_t & right) const override
    {
        return Parent_t::apply(aPlanNode, left, right)->disableAllAndEnableCommutativity();
    };
    
    std::string getName()  const override { return "RightAssociativity_B2"; };

};




#endif
