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
    Join(Bitvector & left, Bitvector & right) :
    Operator<EquivalenceClass, Bitvector>("JOIN"),
    _leftRelations(left),
    _rightRelations(right)
    {};
    
    
    Join(EquivalenceClass & left, Bitvector & right) :  Operator<EquivalenceClass, Bitvector>("name") , _leftRelations(left.getRelations()), _rightRelations(right)
    {
        _left = &left;
    }
    
    Join(Bitvector & left, EquivalenceClass & right) :  Operator<EquivalenceClass, Bitvector>("name") , _leftRelations(left), _rightRelations(right.getRelations())
    {
        _right = &right;
    }
    
    Join(EquivalenceClass & left, EquivalenceClass & right) :  Operator<EquivalenceClass, Bitvector>("name") , _leftRelations(left.getRelations()), _rightRelations(right.getRelations())
    {
        _right = &right;
        _left = &left;
    }
    
    
    const Bitvector & getRelations() //override
    {
        return _leftRelations; //+_rightRelations;
    };

private:
    EquivalenceClass * _left;
    EquivalenceClass * _right;
    Bitvector & _leftRelations;
    Bitvector & _rightRelations;
};

#endif
