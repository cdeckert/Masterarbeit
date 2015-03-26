//
//  main.cpp
//




#include "Executor.h"
#include <string>

#include "JSONAdaptor.h"



int main()
{
	typedef EquivalenceClass_t Ec;
    
    JSONAdaptor<PlanNode_t> adaptor;
    
    std::string input = "{\"relations\":[1,2,3],\"joinEdges\":[{\"from\":1,\"to\":2},{\"from\":2,\"to\":3}],\"query\":{\"op\":\"join\",\"l\":{\"op\":\"scan\",\"l\":1},\"r\":{\"op\":\"join\",\"l\":{\"op\":\"scan\",\"l\":2},\"r\":{\"op\":\"scan\",\"l\":3}}}}";

    Ec * ecs = adaptor.parse(input);
	
    execute(*ecs);
    
    adaptor.dump(ecs);
    return 1;
}