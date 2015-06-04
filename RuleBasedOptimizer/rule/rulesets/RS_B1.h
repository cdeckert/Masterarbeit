//
//  RS_B1.h
//

#ifndef RuleBasedOptimizer_RS_B1_h
#define RuleBasedOptimizer_RS_B1_h

#include "RuleSet.h"
#include "Rule.h"
#include "Commutativity.h"
#include "Swap.h"
#include "LeftAssociativity.h"


/**
 * @brief Rule Set RS_B1
 * @details RS_B1 was introduced by Pellenkoft
 *
 * @tparam Rule_t a abstract rule
 * @tparam PlanNode_t a standard PlanNode
 * @tparam Operations_t Operations
 */
template <typename PlanNode_t, typename Operations_t>
class RS_B1 : public RuleSet<Rule<PlanNode_t, Operations_t>>
{
	typedef RS_B1 self_type;
	typedef Rule<PlanNode_t, Operations_t> Rule_t;
	typedef RuleSet<Rule_t> RuleSet_t;
	typedef CommutativityRule<PlanNode_t, Operations_t> Commutativity_t;
	typedef Swap<PlanNode_t, Operations_t> Swap_t;
    typedef LeftAssociativity<PlanNode_t, Operations_t> LeftAssociativity_t;

public:
	RS_B1() : RuleSet<Rule_t>()
	{
		this->_rules.push_back(new Commutativity_t());
		this->_rules.push_back(new LeftAssociativity_t());
	};

private:

};

#endif
