//
//  TestRuleSetGeneration.h
//

#ifndef __RuleBasedOptimizer__TestRuleSetGeneration__
#define __RuleBasedOptimizer__TestRuleSetGeneration__

#include <stdio.h>
#include <ostream>


class TestRuleSetGeneration
{
    
    
public:
    TestRuleSetGeneration();
    static std::ostream & runTests(std::ostream &);
    static bool testCommutuativity();
};


#endif /* defined(__RuleBasedOptimizer__TestRuleSetGeneration__) */
