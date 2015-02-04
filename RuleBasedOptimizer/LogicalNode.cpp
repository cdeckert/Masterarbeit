//
//  LogicalNode.cpp
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 02/02/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#include "LogicalNode.h"

LogicalNode::LogicalNode(std::string name)
{
    this->name = name;
}

LogicalNode::LogicalNode(LogicalOperator* logicalOperator, LogicalNode* left, LogicalNode* right)
{
    this->logicalOperator = logicalOperator;
    this->logicalNodeLeft = left;
    this->logicalNodeRight = right;
}

bool LogicalNode::isNode()
{
    return this->name.empty();
}

std::string LogicalNode::to_s()
{
    
    if(!this->isNode())
    {
        return this->name;
    }
    else
    {
        std::string result = "";
        result += "("+this->logicalNodeLeft->to_s() + " ";
        result += this->logicalOperator->to_s()+ " ";
        result += ""+this->logicalNodeRight->to_s()+")";
        return result;
    }
    
}

void LogicalNode::applyCommutativity()
{
    LogicalNode * temp = this->logicalNodeRight;
    this->logicalNodeRight = this->logicalNodeLeft;
    this->logicalNodeLeft = temp;
}

void LogicalNode::applyLeftAssociativity()
{
    if(this->logicalNodeRight->isNode())
    {
        this->logicalNodeRight->applyCommutativity();
        LogicalNode * temp = this->logicalNodeRight->logicalNodeLeft;
        this->logicalNodeRight->logicalNodeLeft = this->logicalNodeLeft;
        this->logicalNodeLeft = this->logicalNodeRight;
        this->logicalNodeRight = temp;
    }
}

void LogicalNode::applyRightAssociativity()
{
    if(this->logicalNodeLeft->isNode())
    {
        this->logicalNodeLeft->applyCommutativity();
        LogicalNode * temp = this->logicalNodeLeft->logicalNodeRight;
        this->logicalNodeLeft->logicalNodeRight = this->logicalNodeRight;
        this->logicalNodeRight = this->logicalNodeLeft;
        this->logicalNodeLeft= temp;
    }
}

void LogicalNode::applyRightExchange()
{
    if(this->isNode() && this->logicalNodeLeft->isNode())
    {
        LogicalNode * temp = this->logicalNodeLeft->logicalNodeRight;
        this->logicalNodeLeft->logicalNodeRight = this->logicalNodeRight;
        this->logicalNodeRight = temp;
    }
}


void LogicalNode::applyLeftExchange()
{
    if(this->isNode() && this->logicalNodeRight->isNode())
    {
        LogicalNode * temp = this->logicalNodeRight->logicalNodeLeft;
        this->logicalNodeRight->logicalNodeLeft = this->logicalNodeLeft;
        this->logicalNodeLeft = temp;
    }
}