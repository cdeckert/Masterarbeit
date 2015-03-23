//
//  main.cpp
//




#include "Executor.h"



int main()
{
	Bitvector_t & a = * new Bitvector_t();
	a.set(1);
	
	Bitvector_t & b = * new Bitvector_t();
	b.set(3);
	b.set(2);
	b.set(1);
	b.union_with(a);
	Bitvector_t c;
	c.set_to_difference(b, a);
	//Bitvector_t & c = b-a;
	
	
	EquivalenceClass_t & eq = join(scan(1), scan(2), c);
	
	
    execute(eq);
    return 1;
}