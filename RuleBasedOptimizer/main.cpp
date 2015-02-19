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

    EquivalenceClass_t & generate()
    {
        Bitvector32_t &b1 = *getBitvectorAndSetElement(0);
        Bitvector32_t &b2 = *getBitvectorAndSetElement(1);
        
        PlanNode_BV  *p = new PlanNode_BV(JOIN, b1, b2);
        
        
        EquivalenceClass_t *eq = new EquivalenceClass_t();
        eq->push_back(*p);
        
        for(int i = 2; i < 3; ++i)
        {
            Bitvector32_t *b_new = getBitvectorAndSetElement(i);
            PlanNode_BV * pn = new PlanNode_BV(JOIN, *b_new, *eq);
            pn->print(std::cout);
            std::cout << std::endl << std::endl << std::endl;
            std::cout.flush();
            eq = new EquivalenceClass_t();
            eq->push_back(*pn);
            
            eq->printFirst(std::cout);
            std::cout << std::endl << std::endl << std::endl;
            std::cout.flush();
            
        }
        
        
        for(EquivalenceClass_t::Iterator itr = eq->begin(); itr != eq->end(); ++itr)
        {
            std::cout << itr->getRelations() << std::endl;
        }
        
        eq->printFirst(std::cout);
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
    
    eq.printFirst(std::cout);
    
    t.apply(eq);
    
    std::cout << std::endl << "*************************************";
    std::cout << std::endl << "*************************************" << std::endl;
    std::cout << eq.size() << std::endl;
    
    
    //std::cout << eq.size() << std::endl;

    /* Bitvector32_t &&t1 = Bitvector32_t();
     t1.set(3);
     Bitvector32_t &&t2 = Bitvector32_t();
     t2.set(4);
     t1 += t2;
     t1.print(std::cout);*/
    return 0;
}