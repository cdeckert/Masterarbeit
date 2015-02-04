//
//  main.cpp
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 02/02/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#include <iostream>

//#include "LogicalNode.h"
#include "TreeGenerator.h"
#include "ExhaustiveTransformation.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    LogicalNode * tree = TreeGenerator::leftDeepTree(10);
    //while
    tree->applyLeftAssociativity();
    std::cout << tree->to_s();
    
    ExhaustiveTransformation<LogicalNode> transformation = new ExhaustiveTransformation<LogicalNode>();
    transformation.execute(*tree);
    
    return 0;
}
