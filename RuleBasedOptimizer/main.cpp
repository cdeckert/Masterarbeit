//
//  main.cpp
//




#include "Executor.h"
#include "Configurator.h"
#include "PlanNode.h"

#include <string>

#include "JSONAdaptor.h"
#include "DotAdaptor.h"
#include "StringAdaptor.h"

#include "CostEstimator.h"


#include "Stopwatch.h"




std::string getConfigPath(int argc, char* argv[])
{
	std::string configPath = "/Users/christiandeckert/Desktop/Masterarbeit_develop/config.json";
	if(argc == 0)
	{
		
	}
	else
	{
		/*for(int i = 0; i < argc; ++i)
		{
			if (argv[i] == "-c")
			{
				configPath = argv[i+1];
			}
			else if(argv[i] == "-h")
			{
				std::cout << "help";
			}
		}*/
	}
	return configPath;
}




int main(int argc, char* argv[])
{
	typedef unsigned int u_int;
	typedef BitVectorSmall<u_int> Bitvector_t;
	typedef PlanNode<Bitvector_t> PlanNode_t;
	typedef PlanNode_t::EquivalenceClass_t Ec;
	// read configuration
	std::string _configPath = getConfigPath(argc, argv);
	Configurator<PlanNode_t> configManager;
	for(Configuration<PlanNode_t> & c : configManager.getConfigurations(_configPath))
	{
		std::cout << "RUN";
		//execute configurations
		Executor<PlanNode_t> exec(c);
		std::cout << "RUN";
		exec.run();
	}
	return 1;
	
	
	
	// execute programm
	
	// store findings
	
	// return 1
	
    /*
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
	
	return 1;*/
};



