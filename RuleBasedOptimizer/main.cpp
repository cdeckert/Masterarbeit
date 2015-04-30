//
//  main.cpp
//

#include <string>



#include "Executor.h"
#include "Configurator.h"
#include "PlanNode.h"
#include "JSONAdaptor.h"
#include "DotAdaptor.h"
#include "StringAdaptor.h"
#include "CostEstimator.h"
#include "Stopwatch.h"




std::string getConfigPath(int argc, char *argv[])
{
	std::string configPath = "/Users/christiandeckert/Desktop/Masterarbeit_develop/config.json";
	if (argc == 0)
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




int main(int argc, char *argv[])
{
	typedef unsigned int u_int;
	typedef BitVectorSmall<u_int> Bitvector_t;
	typedef PlanNode<Bitvector_t> PlanNode_t;
	typedef PlanNode_t::EquivalenceClass_t Ec;

	// read configuration
	std::string _configPath = getConfigPath(argc, argv);
	Configurator<PlanNode_t> configManager;
	for (Configuration<PlanNode_t> &c : configManager.getConfigurations(_configPath))
	{
		Executor<PlanNode_t> exec(c);
		//execute configurations
		exec.run();
	}
	return 1;
};



