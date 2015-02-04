//
//  LogicalOperator.cpp
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 02/02/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//



#include "LogicalOperator.h"


std::unordered_map<std::string, LogicalOperator *> LogicalOperator::logicalOperators;

std::string LogicalOperator::to_s()
{
    return this->identifier;
}

LogicalOperator * LogicalOperator::get(std::string identifier)
{
    if (logicalOperators.count(identifier) == 0)
    {
        logicalOperators.insert(std::make_pair(identifier, new LogicalOperator(identifier)));
    }
    return logicalOperators.at(identifier);
}

LogicalOperator::LogicalOperator(std::string identifier)
{
    this->identifier = identifier;
}