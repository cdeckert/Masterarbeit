//
//  Join.h
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 2/17/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#ifndef RuleBasedOptimizer_Join_h
#define RuleBasedOptimizer_Join_h

#include "Operator.h"

template <typename EquivalenceClass, typename Bitvector>
class Join : public Operator<EquivalenceClass, Bitvector>
{
    
public:
    Join(Bitvector & left, Bitvector & right) : Operator<EquivalenceClass, Bitvector>("name") , _leftRelations(left), _rightRelations(right)
    {
        //_name = "JOIN";
    };
    const Bitvector & getRelations() //override
    {
        return _leftRelations+_rightRelations;
    };

private:
    EquivalenceClass * _left;
    EquivalenceClass * _right;
    Bitvector & _leftRelations;
    Bitvector & _rightRelations;
};

#endif
