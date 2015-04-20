//
//  Configurator.h
//

#ifndef __RuleBasedOptimizer__Configurator__
#define __RuleBasedOptimizer__Configurator__

#include <stdio.h>
#include <vector>
#include <string>

#include "Configuration.h"

struct Configurator
{
	typedef std::vector<Configuration> ConfigurationVector_t;
public:
	ConfigurationVector_t getConfigurations(std::string);
private:
	
};


#endif /* defined(__RuleBasedOptimizer__Configurator__) */
