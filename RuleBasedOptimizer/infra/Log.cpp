//
//  Log.cpp
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 05/05/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#include "Log.h"

Log * Log::instance;

Log & Log::log()
{
	if(instance == NULL)
	{
		instance = new Log();
	}
	return * instance;
}


Log::Log()
{
	
}