//
//  LogicalNode.h
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 02/02/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#ifndef __RuleBasedOptimizer__LogicalNode__
#define __RuleBasedOptimizer__LogicalNode__

#include <stdio.h>
#include <string>

#include "LogicalOperator.h"

#endif /* defined(__RuleBasedOptimizer__LogicalNode__) */


class LogicalNode {
    LogicalNode* logicalNodeLeft;
    LogicalNode* logicalNodeRight;
    LogicalOperator* logicalOperator;
    std::string name;
    
public:
    LogicalNode(std::string);
    LogicalNode(LogicalOperator*, LogicalNode*, LogicalNode*);
    std::string to_s();
    void exchange();
    void applyCommutativity();
    void applyRightAssociativity();
    void applyLeftAssociativity();
    void applyRightExchange();
    void applyLeftExchange();
    bool isNode();
};