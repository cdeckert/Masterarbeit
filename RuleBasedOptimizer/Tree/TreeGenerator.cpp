//
//  TreeGenerator.cpp
//

#include "TreeGenerator.h"


EquivalenceClass<Bitvector> * TreeGenerator::generate()
{
    
    
    EquivalenceClass<Bitvector> * equivalence1 = new EquivalenceClass<Bitvector>::EquivalenceClass();
    PlanNode<Bitvector> * node1 = new PlanNode<Bitvector>(JOIN, 1, 2);
    equivalence1->addNode(node1);
    return equivalence1;
    for(int i = 3; i<10; ++i)
    {
        node1 = new PlanNode<Bitvector>(JOIN, equivalence1, i);
        EquivalenceClass<Bitvector> * equivalence2 = new EquivalenceClass<Bitvector>::EquivalenceClass(node1);
    }
    return  equivalence1;
}