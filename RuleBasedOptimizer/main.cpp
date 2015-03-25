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
    
    std::string input = "{\"relations\":[1,2,3],\"joinEdges\":[{\"from\":1,\"to\":2},{\"from\":1,\"to\":3}],\"query\":{\"op\":\"join\",\"l\":{\"op\":\"scan\",\"l\":1},\"r\":{\"op\":\"join\",\"l\":{\"op\":\"scan\",\"rel\":2},\"r\":{\"op\":\"scan\",\"rel\":3}}}}";

    Ec * ecs = adaptor.parse(input);

	/*Ec & rel1 = rel(1, {2,3});
	Ec & rel2 = rel(2, {1});
	Ec & rel3= rel(3, {1});


	Ec & eq = join(rel1, rel2);*/
	
	
    //execute(eq);
    return 1;
}