//
//  CostEstimator.h
//

#ifndef RuleBasedOptimizer_CostEstimator_h
#define RuleBasedOptimizer_CostEstimator_h


template <typename PlanNode_t>
class CostEstimator
{
	typedef typename PlanNode_t::EquivalenceClass_t EquivalenceClass_t;
	typedef typename EquivalenceClass_t::Iterator EItr;
	typedef typename PlanNode_t::BV Bitvector_t;
	typedef std::unordered_map<Bitvector_t, double, Hasher<Bitvector_t>> BvDoubleMap_t;

public:
	/**
	 * @brief [brief description]
	 * @details [long description]
	 *
	 * @param stats [description]
	 */
	CostEstimator(BvDoubleMap_t, BvDoubleMap_t);
	
	/**
	 * @brief [brief description]
	 * @details [long description]
	 *
	 * @param input [description]
	 */
	void getCheapestPlan(EquivalenceClass_t *);

	/**
	 * @brief [brief description]
	 * @details [long description]
	 *
	 * @param planNode [description]
	 */
	void findCheapestPlan(PlanNode_t *);

private:
	BvDoubleMap_t _cardinality;
	BvDoubleMap_t _selectivity;
	BvDoubleMap_t _cost;
	
	double getSelectivity(PlanNode_t *);
	double calcCost(PlanNode_t *);
	double calcCardinality(PlanNode_t *);
};


//
// Implementation
//

template <typename PlanNode_t>
CostEstimator<PlanNode_t>::CostEstimator(BvDoubleMap_t cardinality, BvDoubleMap_t selectivity)
{
	_cardinality = cardinality;
	_cost = cardinality;
	_selectivity = selectivity;
};


template <typename PlanNode_t>
void CostEstimator<PlanNode_t>::getCheapestPlan(EquivalenceClass_t *input)
{
	double optimalCost = 0.0;
	for (EItr eq = input->begin(); eq.isOK(); ++eq)
	{
		
		double newCardinality = calcCardinality(eq.node());
		double newCost = calcCost(eq.node());
		if(!input->isBest())
		{
			input->setBest(eq.node());
			_cardinality.insert({{input->getRelations(), newCardinality}});
			_cost.insert({{input->getRelations(), newCost}});
		}
		if(optimalCost == 0 || optimalCost > newCost)
		{
			optimalCost = newCost;
			input->setBest(eq.node());
			_cardinality.insert({{input->getRelations(), newCardinality}});
			_cost.insert({{input->getRelations(), optimalCost}});
		}
		
		
		
	}
};


template <typename PlanNode_t>
double CostEstimator<PlanNode_t>::getSelectivity(PlanNode_t * pn){
	double selectivity = 1.0;
	if(!pn->hasRight())
	{
		return selectivity;
	}
	
	for(u_int i = 0; i< pn->l().getRelations().capacity(); ++i)
	{
		for(u_int j = 0; j < pn->r().getRelations().capacity(); ++j)
		{
			Bitvector_t b;
			b.set(i);
			b.set(j);
			if(_selectivity.count(b) != 0)
			{
				selectivity *= _selectivity.at(b);
			}
			
		}
	}
	return selectivity;
};

template <typename PlanNode_t>
double CostEstimator<PlanNode_t>::calcCost(PlanNode_t * planNode)
{
	double cost = 0.0;
	
	if (_cost.count(planNode->l().getRelations()) == 0)
	{
		getCheapestPlan(&planNode->l());
	}
	if (planNode->hasRight() && _cost.count(planNode->r().getRelations()) == 0)
	{
		getCheapestPlan(&planNode->r());
	}
	
	cost += _cost.at(planNode->l().getRelations());
	
	if(planNode->hasRight())
	{
		cost += _cost.at(planNode->r().getRelations());
	}
	
	
	cost += calcCardinality(planNode);
	
	return cost;
};


template <typename PlanNode_t>
double CostEstimator<PlanNode_t>::calcCardinality(PlanNode_t * planNode)
{
	double cardinality = 1.0;
	if (_cardinality.count(planNode->l().getRelations()) == 0)
	{
		getCheapestPlan(&planNode->l());
	}
	
	if (planNode->hasRight() && _cardinality.count(planNode->r().getRelations()) == 0)
	{
		getCheapestPlan(&planNode->r());
	}
	
	cardinality *= _cardinality.at(planNode->l().getRelations());
	if(planNode->hasRight())
	{
		cardinality *= _cardinality.at(planNode->r().getRelations());
	}
	
	if(planNode->hasRight())
	{
		cardinality *= getSelectivity(planNode);
	}
	return cardinality;
};

template <typename PlanNode_t>
void CostEstimator<PlanNode_t>::findCheapestPlan(PlanNode_t *planNode)
{
	u_int givenCardinality;
	if (_cardinality.count(planNode->getRelations()) > 0)
	{
		givenCardinality = _cardinality.at(planNode->getRelations());
	}
	else
	{
		givenCardinality = 0;
	}
	
	if (_cardinality.count(planNode->l().getRelations()) == 0)
	{
		getCheapestPlan(&planNode->l());
	}
	
	if (planNode->hasRight() && _cardinality.count(planNode->r().getRelations()) == 0)
	{
		getCheapestPlan(&planNode->r());
	}
	
	u_int minCardinality = calcPrice(planNode);
	if (givenCardinality == 0 || givenCardinality > minCardinality)
	{
		_cardinality.insert({
			{planNode->getRelations(), minCardinality}
		});
		
	}
};

#endif
