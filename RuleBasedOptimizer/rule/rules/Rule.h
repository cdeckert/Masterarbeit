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
template <typename PlanNode, typename Operations_t>
class Rule
{
    
public:

    Rule() : o(*Operations_t::exemplar()){};
    /**
     * @brief checks whether or not a rule is applicable
     * @details the actual implementation is done in a different class
     * 
     * @param e a specific plan node
     * @return true in case the rule is applicable
     */
    virtual bool isApplicable(PlanNode &) const = 0;
    virtual PlanNode * apply(PlanNode&) const = 0;
    
protected:
    Operations_t & o;

};
#endif
