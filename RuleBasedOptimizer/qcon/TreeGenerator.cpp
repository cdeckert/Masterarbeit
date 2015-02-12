//
//  TreeGenerator.cpp
//

#include "TreeGenerator.h"


EquivalenceClass<Bitvector> * TreeGenerator::generate()
{
    
    
    EquivalenceClass<Bitvector> * equivalence1 = new EquivalenceClass<Bitvector>::EquivalenceClass();
    PlanNode<Bitvector> * node1 = new PlanNode<Bitvector>(JOIN, 1, 2);
    equivalence1->addNode(node1);
    for(int i = 3; i<5; ++i)
    {
        
        node1 = new PlanNode<Bitvector>(JOIN, i, equivalence1);
        equivalence1 = new EquivalenceClass<Bitvector>::EquivalenceClass(node1);
    }
    
    std::cout << equivalence1->toString();
    return  equivalence1;
}