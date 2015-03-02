//
//  Rule.h
//

#ifndef RuleBasedOptimizer_Rule_h
#define RuleBasedOptimizer_Rule_h

#include "Operations.h"

/**
 * @brief basic rule (abstract class)
 */
template <typename PlanNode, typename Operations_t>
class Rule
{
    
public:
    Rule() : o(*Operations_t::exemplar()){};
    
    virtual bool isApplicable(PlanNode &) const = 0;
    virtual PlanNode * apply(PlanNode&) const = 0;
    
protected:
    Operations_t & o;

};
#endif
