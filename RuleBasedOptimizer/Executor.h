
//
//  Executor.h
//

#ifndef RuleBasedOptimizer_Executor_h
#define RuleBasedOptimizer_Executor_h


#include <iostream>

#include <iostream>

#include "Types.h"
#include "Configuration.h"

template <typename PlanNode_t>
class Executor
{
	typedef Configuration<PlanNode_t> Configuration_t;

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
};



void execute(EquivalenceClass_t & e)
{
    
	ExhaustiveTransformation_t t2 = * new ExhaustiveTransformation_t(RS_B0_t());
    t2.apply(e);

}





#endif
