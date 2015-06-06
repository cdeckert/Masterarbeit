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
template <typename PlanNode_t, typename Operations_t>
class LeftAssociativity : public Rule<PlanNode_t, Operations_t>
{
	
	
public:
	/**
	 * @brief checks whether or not left associativity is applicable
	 * @details left associativity is applicable in case the given operation is
	 * "JOIN" the left descendant node is a join
	 *
	 * @param parentNode a given plan node
	 * @return true in case the rule is applicable
	 */
	bool isApplicable(PlanNode_t & parentNode) const override
	{
		// IF ((A ⨝ B) ⨝ C)
		return parentNode.getOperator() == JOIN &&
		isApplicable(parentNode, * parentNode.l().getFirst(), * parentNode.r().getFirst());
	};
	/**
	 * @brief checks whether or not left associativity is applicable
	 * @details left associativity is applicable in case the given operation is
	 * "JOIN" the left descendant node is a join
	 *
	 * @param parentNode a given plan node
	 * @param left the left node
	 * @param right the right node
	 * @return true in case the rule is applicable
	 */
    bool isApplicable(PlanNode_t & parentNode, PlanNode_t & left, PlanNode_t & right) const override
    {
        return parentNode.getOperator() == JOIN && left.getOperator() == JOIN && parentNode.r().isOverlapping(left.r());
    }

	/**
	 * @brief apply left associativity
	 */
	PlanNode_t * apply(PlanNode_t & parentNode) const override
	{
        return apply(parentNode, * parentNode.l().getFirst(), * parentNode.r().getFirst());
    };
	/**
	 * @brief apply left associativity
	 */
    PlanNode_t * apply(PlanNode_t & parentNode, PlanNode_t & left, PlanNode_t & right)  const override
    {
        return & this->o.joinPN(left.l(), *this->o.join(left.r(), parentNode.r()));
    };
    
    std::string getName()  const override { return "LeftAssociativity"; };

};


#endif
