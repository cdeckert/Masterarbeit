//
//  main.cpp
//

#include <iostream>

#include "Types.h"
#include "QueryParser.h"



void abc(int & a) {
    std::cout << a << std::endl;
}


int main(int argc, const char * argv[])
{
    Bitvector32_t && bv = Bitvector32_t(3);
    Join_t join (bv, bv);
    std::cout << "RELLLLL: ";
    join.getRelations().print();
    std::cout << std::endl;
    int &&i = 1;
    PlanNode_t && pn = PlanNode_t(i, bv);
    pn.print();
    
    pn.getRelations().print();
    
    EquivalenceClass_t && eq = EquivalenceClass_t(pn);
    PlanNode_t && pn2 = PlanNode_t(i, bv);
    eq.push(pn);
    eq.push(pn2);
    eq.getRelations().print();
    
    int number = 2;
    int *a = &number;
    abc(number);
    std::cout << *a;
    
    return 0;
}
