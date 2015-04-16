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
	CostEstimator(Statistics_t stats): _statistic(stats){};
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
		double cost = 1;
		if(_minCardinality.count(planNode->l().getRelations()) == 0)
		{
			getCheapestPlan(&planNode->l());
			_minCardinality.insert({{planNode->l().getRelations(), 1}});
		}
		
		cost *= _minCardinality.at(planNode->l().getRelations());
		if(planNode->hasRight())
		{
			if(_minCardinality.count(planNode->r().getRelations()) == 0)
			{
				getCheapestPlan(&planNode->r());
				_minCardinality.insert({{planNode->r().getRelations(), 1}});
			}
			cost *= _minCardinality.at(planNode->r().getRelations());

		}
		
		/*cost *= _statistic.getSelectivity(planNode->l().getRelations(), planNode->r().getRelations());*/
		
		std::cout << std::endl << "COST: "<< cost;
		
		
	}
private:
	
	Statistics_t & _statistic;
	std::unordered_map<Bitvector_t, double, Hasher<Bitvector_t>> _minCardinality;
	
	
};

#endif
