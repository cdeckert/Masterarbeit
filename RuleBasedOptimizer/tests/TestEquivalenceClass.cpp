//
//  TestEquivalenceClass.cpp
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 16/02/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#include "TestEquivalenceClass.h"
#include "EquivalenceClass.h"
#include "TestPlanNode.h"
#include <iostream>

std::ostream & TestEquivalenceClass::runTests(std::ostream & out)
{
    return out << "Test iterator:" << testEquivalenceIterator() << std::endl;
}

bool TestEquivalenceClass::testEquivalenceIterator()
{
    EquivalenceClass<int, TestPlanNode> ec;
    TestPlanNode node;
    for(int i = 0; i<10; i++)
    {
        ec.push(node);
    }
    
    std::cout << ec.getSize();
    return ec.getSize() == 10;
}
