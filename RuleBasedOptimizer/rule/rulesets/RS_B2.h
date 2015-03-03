//
//  RS_B2.h
//

#ifndef RuleBasedOptimizer_RS_B2_h
#define RuleBasedOptimizer_RS_B2_h

#include "RuleSet.h"
#include "Rule.h"
#include "Commutativity_B2.h"
#include "LeftAssociativity_B2.h"
#include "RightAssociativity_B2.h"
#include "Exchange_B2.h"


/**
 * @brief Rule Set RS_B2
 * @details RS_B2 was introduced by Pellenkoft
 *
 * @tparam Rule_t a abstract rule
 * @tparam PlanNode_t a standard PlanNode
 * @tparam Operations_t Operations
 */
template <typename PlanNode_t, typename Operations_t>
class RS_B2 : public RuleSet<Rule<PlanNode_t, Operations_t>>
{
    typedef RS_B2 self_type;
    typedef Rule<PlanNode_t, Operations_t> Rule_t;
    typedef RuleSet<Rule_t> RuleSet_t;
    typedef CommutativityRule_B2<PlanNode_t, Operations_t> Commutativity_t;
    typedef LeftAssociativity_B2<PlanNode_t, Operations_t> LeftAssociativity_t;
    typedef RightAssociativity_B2<PlanNode_t, Operations_t> RightAssociativity_t;
	typedef Exchange_B2<PlanNode_t, Operations_t> Exchange_t;
    
public:
    RS_B2() : RuleSet<Rule_t>(4)
    {
        this->_rules[0] = new Commutativity_t();
        this->_rules[1] = new LeftAssociativity_t();
        this->_rules[2] = new RightAssociativity_t();
		this->_rules[3] = new Exchange_t();
    };
    
private:
    
};

#endif
