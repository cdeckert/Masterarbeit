//
//  main.cpp
//

#include <iostream>

#include <iostream>

#include "TypeReservoirs.h"


int main()
{
    
    Bitvector32_t &b = *getBitvectorAndSetElement(0);
    
    
    
    b.print(std::cout);
    
   /* Bitvector32_t &&t1 = Bitvector32_t();
    t1.set(3);
    Bitvector32_t &&t2 = Bitvector32_t();
    t2.set(4);
    t1 += t2;
    t1.print(std::cout);*/
    return 0;
}