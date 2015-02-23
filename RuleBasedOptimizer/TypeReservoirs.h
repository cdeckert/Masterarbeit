//
//  TypeReservoirs.h
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 18/02/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#ifndef RuleBasedOptimizer_TypeReservoirs_h
#define RuleBasedOptimizer_TypeReservoirs_h

#include "Reservoir.h"
#include "Types.h"


Reservoir<EquivalenceClass_t> * reservoirEC = new Reservoir<EquivalenceClass_t>(300);
Reservoir<PlanNode_t> * reservoirPN = new Reservoir<PlanNode_t>(600);




#endif
