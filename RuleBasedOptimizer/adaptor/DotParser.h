//
//  DotParser.h
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 07/04/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#ifndef __RuleBasedOptimizer__DotParser__
#define __RuleBasedOptimizer__DotParser__

#include <stdio.h>

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <initializer_list>

namespace DotParser {
	
	class DotValue;
	class DotValue final
	{
	public:
		enum Type {RELATION, EDGE, GRAPH};
		
		typedef std::vector<DotValue> array;
		
		Type _type;
		Type type() const {return _type;};
		
		bool isRelation() const { return type() == RELATION; }
		bool isEdge() const { return type() == EDGE; }
		bool isGraph() const { return type() == GRAPH; }
		
		unsigned int _relation;
		array _children;
		
		DotValue(std::string);
		
		bool isNumber(std::string);
	};
	
	class Parser
	{
	public:
		DotValue & parse(std::stringstream);
	};
	
}

#endif /* defined(__RuleBasedOptimizer__DotParser__) */
