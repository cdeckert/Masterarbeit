
//
//  Executor.h
//

#ifndef RuleBasedOptimizer_Executor_h
#define RuleBasedOptimizer_Executor_h


#include <iostream>

#include <iostream>

#include "Types.h"




void execute(EquivalenceClass_t & e)
{
    
	ExhaustiveTransformation_t t2 = * new ExhaustiveTransformation_t(RS_B0_t());
    t2.apply(e);

}





#endif
