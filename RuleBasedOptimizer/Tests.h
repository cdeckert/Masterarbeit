//
//  Tests.h
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 16/02/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#ifndef RuleBasedOptimizer_Tests_h
#define RuleBasedOptimizer_Tests_h

#include "TestRuleSetGeneration.h"
#include "TestEquivalenceClass.h"
#include <iostream>

class Tests {
    
    
public:
    static void run();
};


void Tests::run()
{
    std::cout << &TestRuleSetGeneration::runTests(std::cout << "");
    std::cout << &TestEquivalenceClass::runTests(std::cout << "");
}


#endif
