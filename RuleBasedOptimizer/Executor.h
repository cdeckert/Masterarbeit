
//
//  Executor.h
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 24/02/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#ifndef RuleBasedOptimizer_Executor_h
#define RuleBasedOptimizer_Executor_h


#include <iostream>

#include <iostream>

#include "TypeReservoirs.h"







EquivalenceClass_t & scan(u_int i)
{
    Bitvector_t *b = Bitvector(i);
    
    EquivalenceClass_t *eq = reservoirEC->get_new_entry();
    eq->setRelations(*b);
    PlanNode_t & t = * reservoirPN->get_new_entry();
    t.set(SCAN, *eq);
    eq = reservoirEC->get_new_entry();
    
    eq->push_back(t);
    return *eq;
}

EquivalenceClass_t & join(EquivalenceClass_t &e1, EquivalenceClass_t &e2)
{
    PlanNode_t & t = * reservoirPN->get_new_entry();
    t.set(JOIN, e1, e2);
    EquivalenceClass_t & eq = * reservoirEC->get_new_entry();
    eq.push_back(t);
    return eq;
}

void execute(EquivalenceClass_t & e)
{
    
    std::cout << "input: " << std::endl;
    e.print(std::cout);
    
    std::cout  << std::endl << "SIZE: "<< e.getSize();
    
    ExhaustiveTransformation_t t = *new ExhaustiveTransformation_t();
    t.apply(e);
    
    std::cout << std::endl << std::endl << "output: " << std::endl;
    e.print(std::cout);
    
    std::cout  << std::endl << "SIZE: "<< e.getSize() << std::endl;
}





#endif
