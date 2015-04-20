//
//  Configurator.cpp
//

#include "Configurator.h"


Configurator::ConfigurationVector_t Configurator::getConfigurations(std::string configPath)
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
		Configuration config;
		
		for(json11::Json rel : aConfigJson["relations"].array_items())
		{
			Configuration::Bitvector_t b;
			b.set(rel["id"].int_value());
			config._cardinality.insert({{b, rel["cardinality"].int_value()}});
		}
		
		for(json11::Json sel : aConfigJson["joinEdges"].array_items())
		{
			Configuration::Bitvector_t b;
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