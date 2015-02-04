//
//  LogicalNodeParser.h
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 02/02/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#ifndef __RuleBasedOptimizer__LogicalNodeParser__
#define __RuleBasedOptimizer__LogicalNodeParser__

#include <stdio.h>
#include <string>

#include "LogicalNode.h"

class LogicalNodeParser {
    
public:
    static LogicalNode * parse(std::string);
};

#endif /* defined(__RuleBasedOptimizer__LogicalNodeParser__) */
