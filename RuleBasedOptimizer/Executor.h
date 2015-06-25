
//
//  Executor.h
//

#ifndef RuleBasedOptimizer_Executor_h
#define RuleBasedOptimizer_Executor_h


#include <iostream>

#include <iostream>

#include "ExhaustiveTransformation.h"
#include "Configuration.h"
#include "RS_B0.h"
#include "RS_B1.h"
#include "RS_B2.h"
#include "StringAdaptor.h"
#include "CostEstimator.h"
#include "Stopwatch.h"
#include "GraphRuleSet.h"
#include "BetterTransformation.h"
#include "SimpleCostEstimator.h"
#include "ExpandDAG.h"

template <typename T>
class Executor
{
	typedef T PlanNode_t;
	typedef Configuration<PlanNode_t> Configuration_t;
	typedef BitVectorSmall<u_int> Bitvector_t;
	typedef typename PlanNode_t::EquivalenceClass_t EquivalenceClass_t;
	typedef typename EquivalenceClass_t::Iterator EquivalenceClassIterator_t;
	typedef Operations<PlanNode_t> Operations_t;
	typedef Rule<PlanNode_t, Operations_t> Rule_t;
	typedef RuleSet<Operations_t> RuleSet_t;
	typedef RS_B0<PlanNode_t, Operations_t> RS_B0_t;
	typedef RS_B1<PlanNode_t, Operations_t> RS_B1_t;
	typedef RS_B2<PlanNode_t, Operations_t> RS_B2_t;
	typedef GraphRuleSet<PlanNode_t, Operations_t> GraphRuleSet_t;

	typedef BetterTransformation<PlanNode_t, Operations_t, Rule_t> BetterTransformation_t;
	typedef BetterTransformation_t ExhaustiveTransformation_t;
	//typedef ExpandDAG<PlanNode_t, Operations_t, Rule_t> ExhaustiveTransformation_t;
	//typedef RS_B0<PlanNode_t, Operations_t> RS_B0_t;

public:
	Executor();
	~Executor();
	Executor(Configuration_t &config) : _configuration(config){_watch = new Stopwatch();};
	void run() const;

private:
	Configuration_t &_configuration;
	Stopwatch * _watch;
};

//
// Implementation
//

template <typename T>
void Executor<T>::run() const
{
	SimpleCostEstimator<T> costEstimator = SimpleCostEstimator<T>(_configuration.getCardinality(), _configuration.getSelectivity());
	std::cout << "RUN" << std::endl;
	
	
	for (std::string algo : _configuration.getAlgorithms())
	{
		uint64_t duration = 0;
		for (int i = 0; i < 1; ++i)
		{
			ExhaustiveTransformation_t  * t1 = 0;
			if (algo == "RS_B0")
			{
				LOG(INFO) << "RS-B0";
				t1 = new ExhaustiveTransformation_t(RS_B0_t());
			}
			else if (algo == "RS_B1")
			{
				LOG(INFO) << "RS-B1";
				t1 = new ExhaustiveTransformation_t(RS_B1_t());
			}
			else if(algo == "RS_B2")
			{
				LOG(INFO) << "RS-B2";
				t1 = new ExhaustiveTransformation_t(RS_B2_t());
			}else
			{
				t1 = new ExhaustiveTransformation_t(GraphRuleSet_t(_configuration.getJoinEdges()));
			}

			EquivalenceClass_t & eq = * _configuration.getInitalTree();
			StringAdaptor<PlanNode_t> adaptor;
			

			
			costEstimator.restart();
			
			_watch->start();
			t1->apply(eq);
			costEstimator.findOptimalPlan(eq);
			_watch->stop();
			
			duration += _watch->getDuration();
			std::cout << adaptor.dump(&eq);

			LOG(INFO) << "NUMBER OF EQs:" << eq.countEQs();
			
			//LOG(INFO) << "numberOfPNs:" <<t1->numberOfPNs << std::endl;

			
			
			delete t1;
		}
		duration = duration / 1;
		
		
		LOG(INFO)<< "TIME:"  << duration << std::endl<< std::endl;
	}




};

template <typename T>
Executor<T>::~Executor()
{
	delete _watch;
	delete Operations<PlanNode_t>::exemplar();
}


#endif
