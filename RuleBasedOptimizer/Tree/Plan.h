//
//  Plan.h
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 04/02/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#ifndef __RuleBasedOptimizer__Plan__
#define __RuleBasedOptimizer__Plan__

#include <stdio.h>
#include <vector>

class Equivalence;

enum Operator {JOIN};


/**
 * @
 */
struct Plan {
    Operator rootOperator;
    int identifier;
    std::vector<Equivalence*> children;
    //Bitset rules applied
    
    Plan * unifiedTo = NULL;
    
public:
    Plan(int identifier)
    {
        this->identifier = identifier;
    }
    Plan(int identifier, Operator root)
    {
        this->identifier = identifier;
        this->rootOperator = root;
    }

    
};


#endif /* defined(__RuleBasedOptimizer__Plan__) */
