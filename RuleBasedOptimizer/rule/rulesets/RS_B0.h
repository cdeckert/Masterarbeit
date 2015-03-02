//
//  RS_B0.h
//

#ifndef RuleBasedOptimizer_RS_B0_h
#define RuleBasedOptimizer_RS_B0_h

#include "RuleSet.h"
#include "Rule.h"
#include "Commutativity.h"
#include "LeftAssociativity.h"
#include "RightAssociativity.h"

/**
 * @brief Rule Set RS_B0
 * @details RS_B0 was introduced by Pellenkoft
 * 
 * @tparam Rule_t a abstract rule
 * @tparam PlanNode_t a standard PlanNode
 * @tparam Operations_t Operations
 */
template <typename PlanNode_t, typename Operations_t>
class RS_B0 : public RuleSet< Rule<PlanNode_t, Operations_t>>
{
    typedef Rule<PlanNode_t, Operations_t> Rule_t;
    typedef RS_B0 self_type;
    typedef RuleSet<Rule_t> RuleSet_t;
    typedef CommutativityRule<PlanNode_t, Operations_t> Commutativity_t;
    typedef LeftAssociativity<PlanNode_t, Operations_t> LeftAssociativity_t;
    typedef RightAssociativity<PlanNode_t, Operations_t> RightAssociativity_t;
    
public:
    RS_B0() : RuleSet<Rule_t>(3)
    {
        this->_rules[0] = new Commutativity_t();
        this->_rules[1] = new LeftAssociativity_t();
        this->_rules[2] = new RightAssociativity_t();
    };
    
private:
    
};

#endif
