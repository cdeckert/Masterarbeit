//
//  main.cpp
//




#include "Executor.h"



int main()
{
	typedef EquivalenceClass_t Ec;
	
	Ec & rel1 = rel(1, {2,3});
	Ec & rel2 = rel(2, {1});
	Ec & rel3= rel(3, {1});
	
	
	Ec & eq = join(rel1, rel2);
	
	
    execute(eq);
    return 1;
}