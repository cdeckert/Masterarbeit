//
//  main.cpp
//




#include "Executor.h"



int main()
{
    EquivalenceClass_t & eq = join(join(scan(1), scan(2)).on(13,14), join(scan(3), scan(4)).on(10, 11)).on(11,12);
                                 
    execute(eq);
    return 1;
}