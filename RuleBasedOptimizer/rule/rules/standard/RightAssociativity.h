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
	 * @param parentNode a given plan node
	 * @return true in case the rule is applicable
	 */
	bool isApplicable(PlanNode_t & parentNode) const override
	{
        // IF (A ⨝ (B ⨝ C))
        return parentNode.getOperator() == JOIN && isApplicable(parentNode, * parentNode.l().getFirst(), * parentNode.r().getFirst());
    };
    
    bool isApplicable(PlanNode_t & parentNode, PlanNode_t & left, PlanNode_t & right) const override
    {
        return parentNode.getOperator() == JOIN && right.getOperator() == JOIN && parentNode.l().isOverlapping(right.l());
    };

    /**
    * @brief [brief description]
    * @details [long description]
    *
    * @param parentNode [description]
    * @return [description]
    */
    PlanNode_t * apply(PlanNode_t & parentNode) const override
    {
        return apply(parentNode, *parentNode.l().getFirst(), *parentNode.r().getFirst());
    };
    
    PlanNode_t * apply(PlanNode_t & parentNode, PlanNode_t & left, PlanNode_t & right)  const override
    {
        return & this->o.joinPN(*this->o.join(parentNode.l(), right.l()), right.r());
    };
    
    std::string getName()  const override { return "RightAssociativity"; };

};


#endif
