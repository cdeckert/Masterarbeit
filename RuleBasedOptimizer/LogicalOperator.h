//
//  LogicalOperator.h
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 02/02/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#ifndef __RuleBasedOptimizer__LogicalOperator__
#define __RuleBasedOptimizer__LogicalOperator__

#include <stdio.h>
#include <string>
#include <unordered_map>

#endif /* defined(__RuleBasedOptimizer__LogicalOperator__) */


class LogicalOperator {
    std::string identifier;
    
public:
    static LogicalOperator * get(std::string);
    std::string to_s();

private:
    LogicalOperator(std::string);
    static std::unordered_map<std::string, LogicalOperator *> logicalOperators;
};