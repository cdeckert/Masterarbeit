//
//  main.cpp
//




#include "Executor.h"

 
int main()
{
    Operations_t o = Operations_t();
    EquivalenceClass_t * eq = join(scan(3), join(scan(1),scan(2))); //join(scan(3),join(scan(1), join(scan(2), scan(5))));
                                 
    execute(eq);
    return 1;
}