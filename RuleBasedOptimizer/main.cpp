//
//  main.cpp
//




#include "Executor.h"
#include <string>

#include "JSONAdaptor.h"
#include "DotAdaptor.h"
#include "StringAdaptor.h"

#include "CostEstimator.h"


#include "Stopwatch.h"


int main()
{
	
	typedef EquivalenceClass_t Ec;
    
    JSONAdaptor<PlanNode_t> adaptor;
    
    std::string input = "{\"relations\":[1,2,3],\"joinEdges\":[{\"from\":1,\"to\":2},{\"from\":2,\"to\":3}],\"query\":{\"op\":\"join\",\"l\":{\"op\":\"scan\",\"l\":1},\"r\":{\"op\":\"join\",\"l\":{\"op\":\"scan\",\"l\":2},\"r\":{\"op\":\"scan\",\"l\":3}}}}";

    Ec * ecs = adaptor.parse(input);
	
	Stopwatch watch;
	
	
	
	
	CostEstimator<PlanNode_t>* c = new CostEstimator<PlanNode_t>({
		{Bitvector_t(1), 1}, {Bitvector_t(2), 5}, {Bitvector_t(4), 3}, {Bitvector_t(8), 4}
	},
	{
		{Bitvector_t(1), 0.05}, {Bitvector_t(2), 0.75}, {Bitvector_t(4), 0.25}, {Bitvector_t(8), 0.25}});
	watch.start();
	execute(*ecs);
	c->getCheapestPlan(ecs);
	
	watch.stop();
	
	
    
    //adaptor.dump(ecs);
    
    StringAdaptor<PlanNode_t> stringAdaptor;
	
	
	std::cout << stringAdaptor.dump(ecs);
	
	
	
	std::cout << std::endl << "NANO SECS: " << watch.getTime();
	
	return 1;
}