//
//  GraphRuleSet.h
//

#ifndef RuleBasedOptimizer_GraphRuleSet_h
#define RuleBasedOptimizer_GraphRuleSet_h


#include "RuleSet.h"
#include "Rule.h"
#include "GraphRule.h"


/**
 * @brief Graph Rule Set
 * @details The Graph Ruleset replaces all other rule sets and adds a new rule set based on minCutConservative
 *
 * @tparam Rule_t a abstract rule
 * @tparam PlanNode_t a standard PlanNode
 * @tparam Operations_t Operations
 */
template <typename PlanNode_t, typename Operations_t>
class GraphRuleSet : public RuleSet<Rule<PlanNode_t, Operations_t>>
{
	typedef GraphRuleSet self_type;
	typedef Rule<PlanNode_t, Operations_t> Rule_t;
	typedef RuleSet<Rule_t> RuleSet_t;
	typedef GraphRule<PlanNode_t, Operations_t> GraphRule_t;
	typedef typename PlanNode_t::BV Bitvector_t;
	typedef std::unordered_set<Bitvector_t, Hasher<Bitvector_t>> BvSet_t;

public:
	GraphRuleSet();
	GraphRuleSet(BvSet_t);
};

//
// Implementation
//

template <typename PlanNode_t, typename Operations_t>
GraphRuleSet<PlanNode_t, Operations_t>::GraphRuleSet() : RuleSet<Rule_t>()
{
	this->push_back(new GraphRule_t());
};

template <typename PlanNode_t, typename Operations_t>
GraphRuleSet<PlanNode_t, Operations_t>::GraphRuleSet(BvSet_t bvMap) : RuleSet<Rule_t>()
{
	this->push_back(new GraphRule_t(bvMap));
};


#endif
