
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




void execute(EquivalenceClass_t & e)
{
    
    std::cout << "input: " << std::endl;
    e.print(std::cout);
    
    std::cout  << std::endl << "SIZE: "<< e.getSize();
    
    ExhaustiveTransformation_t t = * new ExhaustiveTransformation_t(RS_B0_t());
    t.apply(e);
    
    std::cout << std::endl << std::endl << "output: " << std::endl;
    e.printEndl(std::cout);
    
    std::cout  << std::endl << "SIZE: "<< e.getSize() << std::endl;
    
    
    t = * new ExhaustiveTransformation_t(RS_B1_t());
    t.apply(e);
    
    std::cout << std::endl << std::endl << "output: " << std::endl;
    e.printEndl(std::cout);
    
    std::cout  << std::endl << "SIZE: "<< e.getSize() << std::endl;
    
    t = * new ExhaustiveTransformation_t(RS_B1_t());
    t.apply(e);
    
    std::cout << std::endl << std::endl << "output: " << std::endl;
    e.printEndl(std::cout);
    
    std::cout  << std::endl << "SIZE: "<< e.getSize() << std::endl;
}





#endif
