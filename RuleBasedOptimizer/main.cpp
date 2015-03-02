//
//  main.cpp
//




#include "Executor.h"

Operations_t * o = Operations_t::exemplar();

EquivalenceClass_t & join(EquivalenceClass_t e1, EquivalenceClass_t e2)
{
    return o->join(e1, e2);
}
EquivalenceClass_t & scan(unsigned int i)
{
    return o->scan(i);
}

int main()
{
    EquivalenceClass_t & eq = join(scan(1), join(scan(2), scan(3)).on(10, 11)).on(11,12);
                                 
    execute(eq);
    return 1;
}