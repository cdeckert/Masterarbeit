//
//  TreeGenerator.cpp
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 03/02/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#include "TreeGenerator.h"
#include <string>


LogicalNode * TreeGenerator::leftDeepTree(int size)
{
    LogicalNode *node1 = new LogicalNode("1");
    if(size == 1)
    {
        return node1;
    }
    else
    {
        LogicalNode *n = TreeGenerator::leftDeepTree(size-1);
        LogicalNode *result = new LogicalNode(LogicalOperator::get("⨝"), new LogicalNode(std::to_string(size)), n);
        return result;
    }
}