//
//  Log.h
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 05/05/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#ifndef __RuleBasedOptimizer__Log__
#define __RuleBasedOptimizer__Log__

#include <stdio.h>
#include "json11.hpp"

class Log
{
	typedef json11::Json Json;
	
public:
	Log();
	static Log & log();
	
private:
	static Log * instance;
	Json json;
};
#endif /* defined(__RuleBasedOptimizer__Log__) */
