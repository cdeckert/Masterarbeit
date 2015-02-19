//
//  BasicRuleSet.h
//

#ifndef RuleBasedOptimizer_BasicRuleSet_h
#define RuleBasedOptimizer_BasicRuleSet_h

#include "Rule.h"


/**
 * @brief collection of rules
 */
template <typename Rule>
class RuleSet
{
public:
    RuleSet();

private:
    std::vector<Rule> rules;
};

#endif
