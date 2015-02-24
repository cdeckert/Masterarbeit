//
//  main.cpp
//




#include "Executor.h"

 
int main()
{
    EquivalenceClass_t eq = join(scan(1), join(scan(2), scan(3)));
                                 
    execute(eq);
    return 1;
}