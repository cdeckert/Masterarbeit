//
//  TestRuleSetGeneration.h
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 16/02/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#ifndef __RuleBasedOptimizer__TestRuleSetGeneration__
#define __RuleBasedOptimizer__TestRuleSetGeneration__

#include <stdio.h>
#include <ostream>

#endif /* defined(__RuleBasedOptimizer__TestRuleSetGeneration__) */

class TestRuleSetGeneration
{
    
    
public:
    TestRuleSetGeneration();
    static std::ostream & runTests(std::ostream &);
    static bool testCommutuativity();
};