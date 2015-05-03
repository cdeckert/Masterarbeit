//
//  BasicRuleSet.h
//

#ifndef RuleBasedOptimizer_BasicRuleSet_h
#define RuleBasedOptimizer_BasicRuleSet_h

#include <vector>

#include "Rule.h"
#include "MinCutConservative.h"


/**
 * @brief Abstract Class for Rule Sets
 * @details Each rule set has to inheritate this class
 *
 * @tparam Rule_t a type which represents rules
 */
template <typename Rule_t>
class RuleSet
{
	typedef std::vector<Rule_t *> Rule_v;

public:
	RuleSet() {};

	/**
	 * @brief getter for rules
	 * @return an array of rules
	 */
	const Rule_v getRules() const
	{
		return _rules;
	};

	void push_back(Rule_t *aRule)
	{
		_rules.push_back(aRule);
	};

	Rule_v _rules;
};

#endif
