//
//  TypeReservoirs.h
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 18/02/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#ifndef RuleBasedOptimizer_TypeReservoirs_h
#define RuleBasedOptimizer_TypeReservoirs_h

#include "Types.h"
#include "Reservoir.h"



Reservoir<Bitvector32_t> bitvectors(100);

Bitvector32_t * getBitvectorAndSetElement(unsigned short element)
{
    Bitvector32_t * b = bitvectors.get_new_entry();
    b->set_only(element);
    return b;
}




#endif
