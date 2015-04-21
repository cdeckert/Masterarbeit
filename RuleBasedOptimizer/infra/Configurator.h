//
//  Configurator.h
//

#ifndef __RuleBasedOptimizer__Configurator__
#define __RuleBasedOptimizer__Configurator__

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "Configuration.h"
#include "json11.hpp"

template<typename PlanNode_t>
struct Configurator
{
	typedef Configurator<PlanNode_t> self_type;
	typedef Configuration<PlanNode_t> Configuration_t;
	typedef std::vector<Configuration_t> ConfigurationVector_t;
	typedef typename Configuration_t::Bitvector_t Bitvector_t;
	
public:
	ConfigurationVector_t getConfigurations(std::string);
private:
	
};


//
// Implementation
//


template <typename PlanNode_t>
typename Configurator<PlanNode_t>::ConfigurationVector_t Configurator<PlanNode_t>::getConfigurations(std::string configPath)
{
	ConfigurationVector_t configurations;
	std::cout << "Config Vector" << std::endl;
	std::cout << configPath;
	std::ifstream configFile(configPath);
	
	std::string jsonInputString;
	std::string line;
	while(std::getline(configFile, line))
	{
		std::cout << line;
	}
	
	configFile.close();
	
	json11::Json inputJson(jsonInputString);
	for(json11::Json aConfigJson : inputJson.array_items())
	{
		Configuration_t config;
		
		for(json11::Json rel : aConfigJson["relations"].array_items())
		{
			Bitvector_t b;
			b.set(rel["id"].int_value());
			config._cardinality.insert({{b, rel["cardinality"].int_value()}});
		}
		
		for(json11::Json sel : aConfigJson["joinEdges"].array_items())
		{
			Bitvector_t b;
			b.set(sel["from"].int_value());
			b.set(sel["to"].int_value());
			config._cardinality.insert({{b, sel["selectivtity"].number_value()}});
		}
		
		for(json11::Json algo : aConfigJson["algorithms"].array_items())
		{
			config._algorithms.push_back(algo.string_value());
		}
		configurations.push_back(config);
	}
	
	return configurations;
};


#endif /* defined(__RuleBasedOptimizer__Configurator__) */
