//
//  main.cpp
//




#include "Executor.h"
#include <string>

#include "JSONAdaptor.h"
#include "DotAdaptor.h"
#include "StringAdaptor.h"

#include "CostEstimator.h"


#include "Statistics.h"
#include "Stopwatch.h"


int main()
{
	
	typedef EquivalenceClass_t Ec;
    
    JSONAdaptor<PlanNode_t> adaptor;
    
    std::string input = "{\"relations\":[1,2,3],\"joinEdges\":[{\"from\":1,\"to\":2},{\"from\":2,\"to\":3}],\"query\":{\"op\":\"join\",\"l\":{\"op\":\"scan\",\"l\":1},\"r\":{\"op\":\"join\",\"l\":{\"op\":\"scan\",\"l\":2},\"r\":{\"op\":\"scan\",\"l\":3}}}}";

    Ec * ecs = adaptor.parse(input);
	
	Stopwatch watch;
	
	
	
	Statistics<Bitvector_t> * s = new Statistics<Bitvector_t>();
	
	CostEstimator<PlanNode_t>* c = new CostEstimator<PlanNode_t>(*s);
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