//
//  Operator.h
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 2/17/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#ifndef RuleBasedOptimizer_Operator_h
#define RuleBasedOptimizer_Operator_h

#include <string>

template <typename EquivalenceClass, typename Bitvector>
class Operator
{
    std::string _name;
public:
    Operator(std::string name)
    {
        _name = name;
    };
    //virtual const Bitvector & getRelations();
};

#endif
