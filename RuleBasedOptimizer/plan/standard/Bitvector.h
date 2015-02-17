//
//  Bitvector.h
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 2/16/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#ifndef RuleBasedOptimizer_Bitvector_h
#define RuleBasedOptimizer_Bitvector_h

#include <iostream>

template <typename T>
class Bitvector
{
    
public:
    Bitvector();
    Bitvector(T);
    Bitvector(const Bitvector & b){};
    
    inline void print() const {std::cout << _value;}
private:
    T _value;
};


template <typename T>
Bitvector<T>::Bitvector()
{
}

template <typename T>
Bitvector<T>::Bitvector(T value)
{
    _value = value;
}

#endif
