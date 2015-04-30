
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

	typedef ExhaustiveTransformation<PlanNode_t, Operations_t, Rule_t> ExhaustiveTransformation_t;
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
	std::cout << "RUN";

	for (std::string algo : _configuration.getAlgorithms())
	{
		uint64_t duration = 0;
		for (int i = 0; i < 1000; ++i)
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
				t1 = new ExhaustiveTransformation_t(GraphRuleSet_t(_configuration.getSelectivity()));
			}

			EquivalenceClass_t *eq = _configuration.getInitalTree();
			StringAdaptor<PlanNode_t> adaptor;
			CostEstimator<PlanNode_t> c(_configuration.getCardinality(), _configuration.getSelectivity());

			Stopwatch watch;

			watch.start();
			t1->apply(*eq);
			c.getCheapestPlan(eq);
			watch.stop();




			duration += watch.getDuration();
			std::cout << adaptor.dump(eq);
		}
		duration = duration / 1000;
		std::cout << std::endl << "TIME:"  << duration << std::endl;
	}




};




#endif
