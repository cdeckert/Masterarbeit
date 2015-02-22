//
//  main.cpp
//

#include <iostream>

#include <iostream>

#include "TypeReservoirs.h"
#include "ExhaustiveTransformation.h"
#include "BasicRuleSet.h"

typedef PlanNode<Bitvector32_t> PlanNode_BV;
typedef EquivalenceClass<PlanNode_BV, Bitvector32_t> EquivalenceClass_t;
typedef ExhaustiveTransformation<EquivalenceClass_t, EquivalenceClass_t::Iterator, PlanNode_BV, Bitvector32_t> ExhaustiveTransformation_t;
typedef Rule<PlanNode_BV> Rule_t;
typedef RuleSet<Rule_t> RuleSet_t;
EquivalenceClass_t *eq;
    EquivalenceClass_t & generate()
    {
        Bitvector32_t &b1 = *getBitvectorAndSetElement(0);
        Bitvector32_t &b2 = *getBitvectorAndSetElement(1);
        
        PlanNode_BV  *p = new PlanNode_BV(JOIN, *PlanNode_BV::getDescendant(b1), *PlanNode_BV::getDescendant(b2));
        
        
        eq = new EquivalenceClass_t();
        eq->push_back(*p);
        
        
        for(int i = 3; i < 5; ++i)
        {
            PlanNode_BV::Descendant * d1 = new PlanNode_BV::Descendant(*eq);
            PlanNode_BV::Descendant * d2 = new PlanNode_BV::Descendant(*getBitvectorAndSetElement(i));
            
            p = new PlanNode_BV(JOIN, *d1, *d2);
            eq = new EquivalenceClass_t();
            eq->push_back(*p);

        }
        
        return *eq;
    }




/**
 * @brief implements a right deep tree for tests
 */

int main()
{
    EquivalenceClass_t & eq =  generate();
    
    ExhaustiveTransformation_t t;
    
    
    std::cout << std::endl << "*************************************";
    std::cout << std::endl << "*************************************" << std::endl;
    
    std::cout << eq.size() << std::endl;
    
    //eq.printFirst(std::cout);
    
    t.apply(eq);
    
    std::cout << std::endl << "*************************************";
    std::cout << std::endl << "*************************************" << std::endl;
    std::cout << eq.size();
    std::cout << std::endl << "*************************************";
    
    unsigned int i = 0;
    for(std::string s : eq.getStringVector())
    {
        std::cout  << std::endl << i << ":" << s;
        i++;
    }
    
    
    //std::cout << eq.size() << std::endl;

    /* Bitvector32_t &&t1 = Bitvector32_t();
     t1.set(3);
     Bitvector32_t &&t2 = Bitvector32_t();
     t2.set(4);
     t1 += t2;
     t1.print(std::cout);*/
    return 1;
}