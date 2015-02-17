//
//  main.cpp
//  standardplantest
//
//  Created by Christian Deckert on 2/17/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#include <iostream>

#include "PlanNode.h"
#include "Bitvector.h"
#include "EquivalenceClass.h"

typedef Bitvector<unsigned int> Bitvector32_t;
typedef PlanNode<int, Bitvector32_t> PlanNode_t;
typedef EquivalenceClass<PlanNode_t, Bitvector32_t> EquivalenceClass_t;


void abc(int & a) {
    std::cout << a << std::endl;
}


int main(int argc, const char * argv[])
{
    Bitvector32_t && bv = Bitvector32_t(3);
    
    bv.print();
    int &&i = 1;
    PlanNode_t && pn = PlanNode_t(i, bv);
    pn.print();
    
    pn.getRelations().print();
    
    EquivalenceClass_t && eq = EquivalenceClass_t(pn);
    eq.getRelations().print();
    //b;//.print();
    
    int number = 2;
    int *a = &number;
    abc(number);
    std::cout << *a;
    return 0;
}
