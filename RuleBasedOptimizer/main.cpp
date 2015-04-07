//
//  main.cpp
//




#include "Executor.h"
#include <string>

#include "JSONAdaptor.h"
#include "DotAdaptor.h"
#include "StringAdaptor.h"


#include "Statistics.h"



int main()
{
	typedef EquivalenceClass_t Ec;
    
    JSONAdaptor<PlanNode_t> adaptor;
    
    std::string input = "{\"relations\":[1,2,3],\"joinEdges\":[{\"from\":1,\"to\":2},{\"from\":2,\"to\":3}],\"query\":{\"op\":\"join\",\"l\":{\"op\":\"scan\",\"l\":1},\"r\":{\"op\":\"join\",\"l\":{\"op\":\"scan\",\"l\":2},\"r\":{\"op\":\"scan\",\"l\":3}}}}";

    Ec * ecs = adaptor.parse(input);
	
	Statistics<Bitvector_t> * s = new Statistics<Bitvector_t>();
	
    execute(*ecs);
    
    adaptor.dump(ecs);
    
    StringAdaptor<PlanNode_t> stringAdaptor;
	
	
	std::cout << stringAdaptor.dump(ecs);

	return 1;
}