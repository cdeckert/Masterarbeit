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
	typedef typename PlanNode_t::Bitvector_t Bitvector_t;
	
	typedef std::unordered_map<Bitvector_t, double, Hasher<Bitvector_t>> BvDoubleMap_t;
public:
	/**
	 * @brief [brief description]
	 * @details [long description]
	 *
	 * @param stats [description]
	 */
	CostEstimator(BvDoubleMap_t cardinality)
	{
		_cardinality.insert(cardinality);
		_cost.insert(cardinality);
		
		_selectivity.insert({
			{Bitvector_t(1), 0.05}, {Bitvector_t(2), 0.75}, {Bitvector_t(4), 0.25}, {Bitvector_t(8), 0.25}
		});
		printMap();
	};
	
	
	
	/**
	 * @brief [brief description]
	 * @details [long description]
	 *
	 * @param input [description]
	 */
	void getCheapestPlan(EquivalenceClass_t *input)
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
			if(optimalCost > newCost)
			{
				optimalCost = newCost;
				input->setBest(eq.node());
				_cardinality.insert({{input->getRelations(), newCardinality}});
				_cost.insert({{input->getRelations(), optimalCost}});
			}
			
			
			
		}
	}

	
	double calcCardinality(PlanNode_t * planNode)
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
		
		std::cout << "cardinality: " << cardinality << std::endl;
		
		return cardinality;
	}
	
	double calcCost(PlanNode_t * planNode)
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

		std::cout << "COST: " << cost << std::endl;
		
		return cost;
	}

	/**
	 * @brief [brief description]
	 * @details [long description]
	 *
	 * @param planNode [description]
	 */
	void findCheapestPlan(PlanNode_t *planNode)
	{
		u_int givenCardinality;


		std::cout << std::endl << "find Cheapest Plan";

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

			std::cout << "getCheapestPlan(&planNode->l());" << std::endl;
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
			
			
			printMap();
		}

		std::cout << std::endl << "END: find Cheapest Plan";


	}
	/**
	 * @brief [brief description]
	 * @details [long description]
	 */
	void printMap()
	{
		std::cout << std::endl << std::endl << "KEY MAP::::" << std::endl;
		for (auto kv : _cardinality)
		{
			std::cout << kv.first << ": " << kv.second << std::endl;
		}
	}
	
	
	
	double getSelectivity(PlanNode_t * pn)
	{
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
	}
private:

	BvDoubleMap_t _cardinality;
	BvDoubleMap_t _selectivity;
	BvDoubleMap_t _cost;


};

#endif
