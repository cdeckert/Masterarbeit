
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

template <typename PlanNode_t>
class Executor
{
	typedef Configuration<PlanNode_t> Configuration_t;
	typedef BitVectorSmall<u_int> Bitvector_t;
	typedef typename PlanNode_t::EquivalenceClass_t EquivalenceClass_t;
	typedef typename EquivalenceClass_t::Iterator EquivalenceClassIterator_t;
	typedef Operations<PlanNode_t, u_int> Operations_t;
	typedef Rule<PlanNode_t, Operations_t> Rule_t;
	typedef RuleSet<Operations_t> RuleSet_t;
	typedef RS_B0<PlanNode_t, Operations_t> RS_B0_t;
	typedef RS_B1<PlanNode_t, Operations_t> RS_B1_t;
	typedef RS_B2<PlanNode_t, Operations_t> RS_B2_t;
	typedef GraphRuleSet<PlanNode_t, Operations_t> GraphRuleSet_t;

	typedef BetterTransformation<PlanNode_t, Operations_t, Rule_t> BetterTransformation_t;
	//typedef ExhaustiveTransformation<PlanNode_t, Operations_t, Rule_t> ExhaustiveTransformation_t;
	typedef BetterTransformation_t ExhaustiveTransformation_t;
	//typedef RS_B0<PlanNode_t, Operations_t> RS_B0_t;

public:
	Executor();
	Executor(Configuration_t &config) : _configuration(config) {};
	void run() const;

private:
	Configuration_t &_configuration;
};

//
// Implementation
//

template <typename PlanNode_t>
void Executor<PlanNode_t>::run() const
{
	std::cout << "RUN" << std::endl;
	
	SimpleCostEstimator<PlanNode_t> *c = new SimpleCostEstimator<PlanNode_t>(_configuration.getCardinality(), _configuration.getSelectivity());
	Stopwatch watch;
	for (std::string algo : _configuration.getAlgorithms())
	{
		uint64_t duration = 0;
		for (int i = 0; i < 1; ++i)
		{
			ExhaustiveTransformation_t *t1 = 0;
			if (algo == "RS_B0")
			{
				t1 = new ExhaustiveTransformation_t(RS_B0_t());
			}
			else if (algo == "RS_B1")
			{

				t1 = new ExhaustiveTransformation_t(RS_B1_t());
			}
			else if(algo == "RS_B2")
			{
				t1 = new ExhaustiveTransformation_t(RS_B2_t());
			}else
			{
				t1 = new ExhaustiveTransformation_t(GraphRuleSet_t(_configuration.getJoinEdges()));
			}

			EquivalenceClass_t *eq = _configuration.getInitalTree();
			StringAdaptor<PlanNode_t> adaptor;
			

			
			c->restart();
			watch.start();
			t1->apply(*eq);
			c->findOptimalPlan(*eq);
			
			watch.stop();




			duration += watch.getDuration();
			std::cout << adaptor.dump(eq);
		}
		duration = duration / 1;
		std::cout << std::endl << "TIME:"  << duration << std::endl;
	}




};




#endif
