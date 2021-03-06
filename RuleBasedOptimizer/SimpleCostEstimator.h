//
//  SimpleCostEstimator.h
//

#ifndef RuleBasedOptimizer_SimpleCostEstimator_h
#define RuleBasedOptimizer_SimpleCostEstimator_h


/**
 * @brief A concrete cost estimator
 * @details This cost estimator implements the interface provided by CostEstimator.h
 *
 * @tparam PlanNode_t A standard PlanNode
 */
template <typename PlanNode_t>
class SimpleCostEstimator : public CostEstimator<PlanNode_t>
{
	typedef typename PlanNode_t::EquivalenceClass_t EquivalenceClass_t;
	typedef typename EquivalenceClass_t::Iterator EItr;
	typedef typename PlanNode_t::BV Bitvector_t;
	typedef std::unordered_map<Bitvector_t, double, Hasher<Bitvector_t>> BvDoubleMap_t;

public:
	/**
	 * @brief Constructor for cost estimation
	 * @details The constructor of cost estimation has to be initalized by cardiality and selectivity
	 *
	 * @param cardinality the cardinality of base relations
	 * @param selectivity the selectivity between two base relations
	 */
	SimpleCostEstimator(BvDoubleMap_t cardiality, BvDoubleMap_t selectivity) ;

	/**
	 * @brief generates cheapest plan for a given equivalence class
	 * @details generates cheapest plan for a given equivalence class by using a cost function
	 *
	 * @param input a given equivaelnce class
	 */
	void findOptimalPlan(EquivalenceClass_t &) override;
	void restart();

private:
	BvDoubleMap_t _cardinality;
	BvDoubleMap_t _selectivity;

	static BvDoubleMap_t _tempCardinality;
	static BvDoubleMap_t _tempCost;


	double getSelectivity(PlanNode_t &);
};



//
// Implementation
//

template <typename PlanNode_t>
std::unordered_map<typename PlanNode_t::BV, double, Hasher<typename PlanNode_t::BV>>
		SimpleCostEstimator<PlanNode_t>::_tempCardinality;

template <typename PlanNode_t>
std::unordered_map<typename PlanNode_t::BV, double, Hasher<typename PlanNode_t::BV>>
		SimpleCostEstimator<PlanNode_t>::_tempCost;

template <typename PlanNode_t>
SimpleCostEstimator<PlanNode_t>::SimpleCostEstimator(BvDoubleMap_t cardinality, BvDoubleMap_t selectivity) : CostEstimator<PlanNode_t>()
{
	_cardinality = cardinality;
	_selectivity = selectivity;
};

template <typename PlanNode_t>
double
SimpleCostEstimator<PlanNode_t>::getSelectivity(PlanNode_t & pn)
{
	double selectivity = 1.0;
	if (!pn.hasRight())
	{
		return selectivity;
	}
	else
	{
		Bitvector_t leftNeighbors; leftNeighbors.set_to_difference(pn.l().getRelations(), pn.r().getNeighbors());
		Bitvector_t rightNeighbors; rightNeighbors.set_to_difference(pn.r().getRelations(), pn.l().getNeighbors());
		Bitvector_t pairOfRelationsToSearchFor;
		for (u_int i = 0; i < leftNeighbors.capacity(); ++i)
		{
			if (leftNeighbors.test(i))
			{
				for (u_int j = 0; j < rightNeighbors.capacity(); ++j)
				{
					if (leftNeighbors.test(i))
					{
						pairOfRelationsToSearchFor.clear(),
														 pairOfRelationsToSearchFor.set(i);
						pairOfRelationsToSearchFor.set(j);
						if (_selectivity.count(pairOfRelationsToSearchFor) != 0)
						{
							selectivity *= _selectivity.at(pairOfRelationsToSearchFor);

						}
					}
				}
			}
		}
		return selectivity;
	}
};

template <typename PlanNode_t>
void
SimpleCostEstimator<PlanNode_t>::restart()
{
	_tempCardinality.clear();
	_tempCost.clear();
	_tempCardinality = _cardinality;
	_tempCost = _cardinality;
};

template <typename PlanNode_t>
void
SimpleCostEstimator<PlanNode_t>::findOptimalPlan(EquivalenceClass_t & eq)
{
	// in case there is no best plan
	if (!eq.isBest())
	{
		double lowestCost;
		if (_cardinality.count(eq.getRelations()) != 0)
		{
			lowestCost = _tempCost.at(eq.getRelations());
		}
		else
		{
			lowestCost = -1;
		}
		for (EItr eqItr = eq.begin(); eqItr.isOK(); ++eqItr)
		{
			PlanNode_t & aPlanNode = * eqItr.node();

			// in case it is a scan there are no alternatives therefore the first planNode is optimal
			if (aPlanNode.getOperator() == SCAN)
			{
				eq.setBest(& aPlanNode);
				return;
			}
			else
			{

				// find optimal plans for child nodes
				if (!aPlanNode.l().isBest())
				{
					findOptimalPlan(aPlanNode.l());
				}
				if (aPlanNode.hasRight() && !aPlanNode.r().isBest())
				{
					findOptimalPlan(aPlanNode.r());
				}
				// calc cardinality and costs
				double newCost = 0;
				double newCardinality = 0;
				try
				{
					newCardinality = _tempCardinality.at(aPlanNode.l().getRelations()) * _tempCardinality.at(aPlanNode.r().getRelations()) * getSelectivity(aPlanNode);
					newCost = newCardinality + _tempCost.at(aPlanNode.l().getRelations()) +  _tempCost.at(aPlanNode.r().getRelations());
				} catch (std::exception e)
				{
					LOG(INFO) << aPlanNode.l().getRelations();
					newCost = 9999999999999;
				}
				// in case costs are lower this line is visited for the first time
				// create a new entry in the cardinality map and in the cost map
				if (newCost < lowestCost || lowestCost == -1)
				{
					eq.setBest(& aPlanNode);
					lowestCost = newCost;
					_tempCardinality.insert({{aPlanNode.getRelations(), newCardinality}});
					_tempCost.insert({{aPlanNode.getRelations(), newCost}});
				}
			}
		}
		return;
	}
};


#endif
