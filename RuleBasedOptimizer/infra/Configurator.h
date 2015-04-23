//
//  Configurator.h
//


// todo combine with Configuration.h
#ifndef __RuleBasedOptimizer__Configurator__
#define __RuleBasedOptimizer__Configurator__

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Configuration.h"
#include "json11.hpp"

template<typename PlanNode_t>
struct Configurator
{
	typedef Configurator<PlanNode_t> self_type;
	typedef Configuration<PlanNode_t> Configuration_t;
	typedef std::vector<Configuration_t> ConfigurationVector_t;
public:
	ConfigurationVector_t getConfigurations(std::string);
};


//
// Implementation
//

template <typename PlanNode_t>
typename Configurator<PlanNode_t>::ConfigurationVector_t Configurator<PlanNode_t>::getConfigurations(std::string configPath)
{
	ConfigurationVector_t configurations;

	// read file
	std::ifstream configFile(configPath);
	std::stringstream contents; contents << configFile.rdbuf();
	configFile.close();




	std::string err;
	json11::Json inputJson = json11::Json::parse(contents.str(), err);

	for (json11::Json aConfigJson : inputJson.array_items())
	{
		Configuration_t config(aConfigJson);
		configurations.push_back(config);
	}
	return configurations;
};


#endif /* defined(__RuleBasedOptimizer__Configurator__) */
