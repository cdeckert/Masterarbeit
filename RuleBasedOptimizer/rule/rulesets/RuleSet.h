//
//  BasicRuleSet.h
//

#ifndef RuleBasedOptimizer_BasicRuleSet_h
#define RuleBasedOptimizer_BasicRuleSet_h

#include "Rule.h"



/**
 * @brief Abstract Class for Rule Sets
 * @details Each rule set has to inheritate this class
 * 
 * @tparam Rule_t a type which represents rules
 */
template <typename Rule_t>
class RuleSet
{
public:
    RuleSet(){};
    /**
     * @brief Rule Set constructor initalized by size
     * @details A rule set constructor which initalizes an array of rule pointers
     * 
     * @param int size of array
     */
    RuleSet(unsigned int size)
    {
        _rules = new Rule_t*[size];
        _size = size;
    };
    /**
     * @brief getter for rules
     * @return an array of rules
     */
    Rule_t ** getRules()
    {
        return _rules;
    }

    Rule_t ** _rules;
    unsigned int _size;
};

#endif
