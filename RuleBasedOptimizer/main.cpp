//
//  main.cpp
//




#include "Executor.h"

Operations_t * o = Operations_t::exemplar();
int main()
{
    
    EquivalenceClass_t & eq = o->join(o->scan(3), o->join(o->scan(1),o->scan(2))); //join(scan(3),join(scan(1), join(scan(2), scan(5))));
                                 
    execute(eq);
    return 1;
}