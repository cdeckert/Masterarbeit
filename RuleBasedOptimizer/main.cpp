//
//  main.cpp
//




#include "Executor.h"



int main()
{
	Bitvector_t neighbourhood;
	neighbourhood.set(1).set(2);
	
	
	EquivalenceClass_t & eq = join(scan(1), scan(2), neighbourhood);
	
	
    execute(eq);
    return 1;
}