//
//  main.cpp
//
//  Created by Christian Deckert on 02/02/15.
//

#include <iostream>
#include "TreeGenerator.h"
#include "ExhaustiveTransformation.h"
#include "Rule.h"


int main(int argc, const char * argv[]) {
    std::cout << "Start!\n";
    
    
    
    Bitvector b(2^5-1);
    b.print(std::cout);
    
    std::cout << "\n\n";
    
    //Reservoir<Plan> * planReservoir = new Reservoir<Plan>(30);
    //planReservoir->get_new_entry();
     EquivalenceClass<Bitvector> * equivalence = TreeGenerator::generate();
    
    typedef ExhaustiveTransformation<EquivalenceClass<Bitvector>, PlanNode<Bitvector>, Rule<EquivalenceClass<Bitvector>, PlanNode<Bitvector>>> Transformation;
    
    Transformation * transformation = new Transformation::ExhaustiveTransformation(new Rule<EquivalenceClass<Bitvector>, PlanNode<Bitvector>>());
    
    transformation->execute(equivalence);
    std::cout << "\nEnd!\n";
    return 0;
}
