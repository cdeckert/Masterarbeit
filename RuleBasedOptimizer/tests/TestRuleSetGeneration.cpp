//
//  TestRuleSetGeneration.cpp
//  RuleBasedOptimizer
//
//

#include "TestRuleSetGeneration.h"
#include "Commutativity.h"
#include "TestPlanNode.h"


TestRuleSetGeneration::TestRuleSetGeneration()
{}

std::ostream & TestRuleSetGeneration::runTests(std::ostream & out)
{
    out << "testCommutuativity:" << testCommutuativity() << std::endl;
    return out;
}



bool TestRuleSetGeneration::testCommutuativity()
{
    Commutativity<TestPlanNode> commu;
    TestPlanNode n = TestPlanNode();
    TestPlanNode newNode = commu.apply(n);
    return  commu.apply(newNode) == n;
}


/*bool TestRuleSetGeneration::testLeftAssociativity()
{
    LeftAssociativity<TestPlanNode> leftAssociativity;
    TestPlanNode n = TestPlanNode();
    TestPlanNode newNode = commu.apply(n);
    return  commu.apply(newNode) == n;
}*/