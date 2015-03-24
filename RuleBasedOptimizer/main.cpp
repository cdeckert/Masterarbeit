//
//  main.cpp
//




#include "Executor.h"



int main()
{	
	EquivalenceClass_t & eq =
	join
	(
		join
		(
			join(1,2,{1,2}),
			3,
			{2,3}
		),
		4,
		{2,3,4}
	 );
	
	
    execute(eq);
    return 1;
}