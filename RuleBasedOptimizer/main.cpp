//
//  main.cpp
//




#include "Executor.h"



int main()
{
    EquivalenceClass_t & eq = join(scan(1), join(scan(2), scan(3)).on(10, 11)).on(11,12);
                                 
    execute(eq);
    return 1;
}