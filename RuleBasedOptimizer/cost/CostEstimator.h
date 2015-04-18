//
//  CostEstimator.h
//

#ifndef RuleBasedOptimizer_CostEstimator_h
#define RuleBasedOptimizer_CostEstimator_h

#include "Statistics.h"


template <typename PlanNode_t>
class CostEstimator
{
	typedef typename PlanNode_t::EquivalenceClass_t EquivalenceClass_t;
	typedef typename EquivalenceClass_t::Iterator EItr;
	typedef typename PlanNode_t::Bitvector_t Bitvector_t;
	typedef Statistics<Bitvector_t> Statistics_t;
public:
	CostEstimator(Statistics_t stats): _statistic(stats)
	{
		_minCardinality.insert({
			{Bitvector_t(1), 1}, {Bitvector_t(2), 2}, {Bitvector_t(4), 3}, {Bitvector_t(8), 4}
		});
		printMap();
	};
	double calcPlanCost(PlanNode_t & planNode)
	{
		planNode.l().getSignature();
	};
	
	void getCheapestPlan(EquivalenceClass_t * input)
	{
		for(EItr eq = input->begin(); eq.isOK(); ++eq)
		{
			findCheapestPlan(eq.node());
		}
	}
	
	
	
	void findCheapestPlan(PlanNode_t * planNode)
	{
		u_int givenCardinality;
		
		
		std::cout << std::endl << "find Cheapest Plan";
		
		if(_minCardinality.count(planNode->getRelations()) > 0)
		{
			givenCardinality = _minCardinality.at(planNode->getRelations());
		}
		else
		{
			givenCardinality = 0;
		}
		
		
		if(_minCardinality.count(planNode->l().getRelations()) == 0)
		{
			getCheapestPlan(&planNode->l());
			
			std::cout << "getCheapestPlan(&planNode->l());" << std::endl;
		}
		if(planNode->hasRight() && _minCardinality.count(planNode->r().getRelations()) == 0)
		{
			getCheapestPlan(&planNode->r());
		}
		
		u_int minCardinality = calcPrice(planNode);
		
		if(givenCardinality == 0 || givenCardinality > minCardinality)
		{
			_minCardinality.insert({
				{planNode->getRelations(), minCardinality}
			});
			printMap();
		}
		
		std::cout << std::endl << "END: find Cheapest Plan";
		
		
	}
	
	void printMap()
	{
		std::cout << std::endl << std::endl << "KEY MAP::::" << std::endl;
		for(auto kv : _minCardinality)
		{
			std::cout << kv.first << ": " << kv.second << std::endl;
		}
	}
	
	double calcPrice(PlanNode_t * planNode)
	{
		double cost = 1;
		std::cout << std::endl << planNode->l().getRelations() << std::endl;
		
		std::cout.flush();
		try {
			
			cost *= _minCardinality.at(planNode->l().getRelations());

		} catch (const std::exception& ex) {
			
			printMap();
			std::cout << "error AT: " << planNode->l().getRelations();
			
			std::cout << std::endl<< "ERROR: " << &ex << std::endl;
			std::cout.flush();
		}
		
		
		if(planNode->hasRight())
		{
			try {
				cost *= _minCardinality.at(planNode->r().getRelations());
				
			} catch (const std::exception& ex) {
				
			}
		}
		
		cost *= _statistic.getSelectivity(planNode->l().getRelations(), planNode->r().getRelations());
		
		std::cout << std::endl << "COST: "<< cost;
		return cost;
	}
private:
	
	Statistics_t & _statistic;
	std::unordered_map<Bitvector_t, double, Hasher<Bitvector_t>> _minCardinality;
	
	
};

#endif
