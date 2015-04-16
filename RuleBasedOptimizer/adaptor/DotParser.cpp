//
//  DotParser.cpp
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 07/04/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#include "DotParser.h"
#include <ctype.h>

namespace DotParser {


	DotValue::DotValue(std::string value)
	{
		if(value == "--")
		{
			_type = EDGE;
		}
		else if(isNumber(value))
		{
			_type = RELATION;
			_relation = std::stoi(value);
		}
		else if(value == "graph")
		{
			_type = GRAPH;
		}
	};
	
	
	bool DotValue::isNumber(std::string word)
	{
		for(std::string::const_iterator k = word.begin(); k != word.end(); ++k)
		{
			if(!isdigit(*k))
			{
				return false;
			}

		}
		return true;
	}
	
	
	/*DotValue & Parser::parse(std::stringstream input)
	{
		DotValue * graph = new DotValue("graph");
		
		for(std::string line : input.getline())
		{
			
		}
		
		return * graph;
	}*/

}

