//
//  CostEstimator.h
//

#ifndef RuleBasedOptimizer_CostEstimator_h
#define RuleBasedOptimizer_CostEstimator_h

/**
 * @brief Cost Estimation
 * @details This class is responsible to estimate the actual cost for a given plan
 *
 * @tparam PlanNode_t a standard planNode
 */
template <typename PlanNode_t>
class CostEstimator
{
	typedef typename PlanNode_t::EquivalenceClass_t EquivalenceClass_t;

public:
	/**
	 * @brief finds the optimal plan out of a bunch of alternative plans
	 * @details Using dynamic programming the method searches for the optimal
	 * plan by choosing for each node which is part of the Equivalence class
	 * which of the plans is the optimal plan
	 *
	 * @param t [description]
	 */
	virtual void findOptimalPlan(EquivalenceClass_t &) = 0;
};


#endif
