//
//  Rule.h
//

#ifndef RuleBasedOptimizer_Rule_h
#define RuleBasedOptimizer_Rule_h

#include "Operations.h"

template <typename PlanNode, typename Operations_t>
class Rule
{
public:
    Rule()
    {
         o = Operations_t::exemplar();
    };
    virtual PlanNode * apply(PlanNode*) const = 0;
    virtual bool isApplicable(PlanNode &) const = 0;
    
    
protected:
    Operations_t * o;

};
#endif
