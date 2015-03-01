//
//  BasicRuleSet.h
//

#ifndef RuleBasedOptimizer_BasicRuleSet_h
#define RuleBasedOptimizer_BasicRuleSet_h

#include "Rule.h"


/**
 * @brief collection of rules
 */
template <typename Rule_t, typename PlanNode_t, typename Operations_t>
class RuleSet
{
public:
    RuleSet(){};
    RuleSet(unsigned int size)
    {
        _rules = new Rule_t*[size];
        _size = size;
    };
    
    Rule_t ** getRules()
    {
        return _rules;
    }

    Rule_t ** _rules;
    unsigned int _size;
};

#endif
