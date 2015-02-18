//
//  main.cpp
//

#include <iostream>

#include "Types.h"
#include "QueryParser.h"



/*EquivalenceClass_t & generateSimpleTree() {
    // generate Operator
    Bitvector32_t && b1 = Bitvector32_t(1);
    Bitvector32_t && b2 = Bitvector32_t(1);
    Join_t && join1 = Join_t(b1, b2);
    PlanNode_t && pn = PlanNode_t();
    EquivalenceClass_t & eq = EquivalenceClass_t(pn);
    return eq;
}*/

void checkOperators()
{
    typedef Operator<int, int> & ExampleOperator_t;
    typedef Join<int, std::string> ExampleJoin_t;
    ExampleOperator_t & example = ExampleOperator_t("Operator");
    ExampleJoin_t & exampleJoin = ExampleJoin_t(1, 1);
    
    
}

void checkPlanNode()
{
    //PlanNode_t & pn = PlanNode_t();
}




int main(int argc, const char * argv[])
{
    checkOperators();
    checkPlanNode();
    
    
    
    /*Bitvector32_t && bv = Bitvector32_t(3);
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
    eq.push_back(pn);
    eq.push_back(pn2);
    eq.getRelations().print();
    
    int number = 2;
    int *a = &number;
    //abc(number);
    std::cout << *a;
    
    */
    
    return 0;
}
