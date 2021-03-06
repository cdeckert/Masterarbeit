//
//  Rule.h
//

#ifndef RuleBasedOptimizer_Rule_h
#define RuleBasedOptimizer_Rule_h

#include "Operations.h"

/**
 * @brief Abstract Class for Rules
 * @details Each rule has to inheritate this class
 *
 * @tparam PlanNode a Plan node
 * @tparam Operations_t operations which can be applied by rules
 */
template <typename PlanNode_t, typename Operations_t>
class Rule
{
    typedef typename PlanNode_t::EquivalenceClass_t EquivalenceClass_t;

public:
	Rule() : o(*Operations_t::exemplar()) {};
	/**
	 * @brief checks whether or not a rule is applicable
	 * @details the actual implementation is done in a different class
	 *
	 * @param e a specific plan node
	 * @return true in case the rule is applicable
	 */
	virtual bool isApplicable(PlanNode_t &) const = 0;
    virtual bool isApplicable(PlanNode_t &, PlanNode_t &, PlanNode_t &) const = 0;
	virtual PlanNode_t *apply(PlanNode_t &) const = 0;
    virtual PlanNode_t *apply(PlanNode_t &, PlanNode_t &, PlanNode_t &) const = 0;
    virtual std::string getName() const = 0;

protected:
	Operations_t &o;

};
#endif
