//
//  BasicRuleSet.h
//

#ifndef RuleBasedOptimizer_BasicRuleSet_h
#define RuleBasedOptimizer_BasicRuleSet_h

#include <vector>

#include "Rule.h"
//#include "MinCutConservative.h"


/**
 * @brief Abstract Class for Rule Sets
 * @details Each rule set has to inheritate this class
 *
 * @tparam Rule_t a type which represents rules
 */
template <typename Rule_t>
class RuleSet
{
	typedef std::vector<Rule_t *> RuleVector;

public:
	RuleSet() {};
	~RuleSet();

	/**
	 * @brief getter for rules
	 * @return an array of rules
	 */
	const RuleVector getRules() const;
    
    /**
     * @brief add rule to ruleset
     * @param aRule a new rule which is added to the ruleset
     */
	void push_back(Rule_t * aRule);

protected:
	RuleVector _rules;
};

//
// Implementation
//

template <typename Rule_t>
RuleSet<Rule_t>::~RuleSet()
{};

template <typename Rule_t>
const typename RuleSet<Rule_t>::RuleVector RuleSet<Rule_t>::getRules() const
{
	return _rules;
};

template <typename Rule_t>
void RuleSet<Rule_t>::push_back(Rule_t * aRule)
{
	_rules.push_back(aRule);
};


#endif
