//
//  RightAssociativity.h
//

#ifndef RuleBasedOptimizer_RightAssociativity_h
#define RuleBasedOptimizer_RightAssociativity_h

/**
 * @brief Right associativity
 * @details Rule that creates commutative plan nodes based on a given node
 *
 * @tparam PlanNode_t PlanNode
 * @tparam Operations_t basic operations like join and scan
 */
template <typename PlanNode_t, typename Operations_t>
class RightAssociativity : public Rule<PlanNode_t, Operations_t>
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
	bool isApplicable(PlanNode_t & aPlanNode) const override
	{
        // IF (A ⨝ (B ⨝ C))
        return aPlanNode.getOperator() == JOIN && isApplicable(aPlanNode, * aPlanNode.l().getFirst(), * aPlanNode.r().getFirst());
    };
    
    bool isApplicable(PlanNode_t & aPlanNode, PlanNode_t & left, PlanNode_t & right) const override
    {
        return aPlanNode.getOperator() == JOIN && right.getOperator() == JOIN && aPlanNode.l().isOverlapping(right.l());
    };

    /**
    * @brief [brief description]
    * @details [long description]
    *
    * @param aPlanNode [description]
    * @return [description]
    */
    PlanNode_t * apply(PlanNode_t & aPlanNode) const override
    {
        return apply(aPlanNode, *aPlanNode.l().getFirst(), *aPlanNode.r().getFirst());
    };
    
    PlanNode_t * apply(PlanNode_t & aPlanNode, PlanNode_t & left, PlanNode_t & right)  const override
    {
        return & this->o.joinPN(*this->o.join(aPlanNode.l(), right.l()), right.r());
    };
    
    std::string getName()  const override { return "RightAssociativity.h"; };

};


#endif
