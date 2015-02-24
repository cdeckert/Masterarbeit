//
//  RS_B0.h
//

#ifndef RuleBasedOptimizer_RS_B0_h
#define RuleBasedOptimizer_RS_B0_h

#include "Rule.h"


/**
 * @brief collection of rules
 */
template <typename Rule>
class RS_B0 : public RuleSet<Rule>
{
public:
    RS_B0();
    RS_B0(const RS_B0 & aRS_B0){ _rules = aRS_B0._rules; };
    std::vector<Rule> _rules;
private:
    
};

#endif
