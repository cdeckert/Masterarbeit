//
//  main.cpp
//

#include <iostream>

#include <iostream>

#include "TypeReservoirs.h"



EquivalenceClass_t * generate()
{
    EquivalenceClass_t * e = reservoirEC->get_new_entry();
    PlanNode_t * t = reservoirPN->get_new_entry();
    t->set(JOIN, *e, *e);
    e->push_back(*t);
    return e;
}

 


/**
 * @brief implements a right deep tree for tests
 */

int main()
{
    EquivalenceClass_t * e = generate();
    e->print(std::cout);
    return 1;
}