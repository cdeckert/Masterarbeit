
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
#include "StringAdaptor.h"
#include "CostEstimator.h"
#include "Stopwatch.h"

template <typename PlanNode_t>
class Executor
{
	typedef Configuration<PlanNode_t> Configuration_t;
	typedef BitVectorSmall<u_int> Bitvector_t;
	typedef typename PlanNode_t::EquivalenceClass_t EquivalenceClass_t;
	typedef typename EquivalenceClass_t::Iterator EquivalenceClassIterator_t;
	typedef Operations<PlanNode_t, u_int> Operations_t;
	typedef Rule<PlanNode_t, Operations_t> Rule_t;
	typedef RS_B0<PlanNode_t, Operations_t> RS_B0_t;
//	typedef RS_B1<PlanNode_t, Operations_t> RS_B1_t;
//	typedef RS_B2<PlanNode_t, Operations_t> RS_B2_t;
	
	typedef ExhaustiveTransformation<EquivalenceClass_t, EquivalenceClassIterator_t,
	PlanNode_t, Bitvector_t, Operations_t, Rule_t> ExhaustiveTransformation_t;
	//typedef RS_B0<PlanNode_t, Operations_t> RS_B0_t;
	

public:
	Executor();
	Executor(Configuration_t & config) : _configuration(config){};
	void run();

private:
	Configuration_t & _configuration;
};



template <typename PlanNode_t>
void Executor<PlanNode_t>::run()
{
	std::cout << "RUN";
	_configuration.getInitalTree();
	ExhaustiveTransformation_t t1((RS_B0_t()));
	EquivalenceClass_t * eq = _configuration.getInitalTree();
	StringAdaptor<PlanNode_t> adaptor;
	CostEstimator<PlanNode_t> c(_configuration.getCardinality(), _configuration.getSelectivity());
	
	Stopwatch watch;
	
	watch.start();
	t1.apply(*eq);
	c.getCheapestPlan(eq);
	watch.stop();
	
	std::cout << std::endl << "TIME:"  << watch.getDuration() << std::endl;
	
	
	
	std::cout << adaptor.dump(eq);
};



/*void execute(EquivalenceClass_t & e)
{
    
	ExhaustiveTransformation_t t2 = * new ExhaustiveTransformation_t(RS_B0_t());
    t2.apply(e);

}
*/




#endif
