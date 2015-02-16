//
//  TestEquivalenceClass.h
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 16/02/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#ifndef __RuleBasedOptimizer__TestEquivalenceClass__
#define __RuleBasedOptimizer__TestEquivalenceClass__

#include <stdio.h>
#include <ostream>


class TestEquivalenceClass {
    
public:
    static std::ostream & runTests(std::ostream &);

private:
    static bool testEquivalenceIterator();

};


#endif /* defined(__RuleBasedOptimizer__TestEquivalenceClass__) */
