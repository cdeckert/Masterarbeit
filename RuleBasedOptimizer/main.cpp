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
    //Reservoir<Plan> * planReservoir = new Reservoir<Plan>(30);
    //planReservoir->get_new_entry();
     EquivalenceClass<Bitvector> * equivalence = TreeGenerator::generate();
    
    
    ExhaustiveTransformation<EquivalenceClass<Bitvector>, PlanNode<Bitvector>, Rule<EquivalenceClass<Bitvector>, PlanNode<Bitvector>>> * transformation = new ExhaustiveTransformation<EquivalenceClass<Bitvector>, PlanNode<Bitvector>, Rule<EquivalenceClass<Bitvector>, PlanNode<Bitvector>>>::ExhaustiveTransformation(new Rule<EquivalenceClass<Bitvector>, PlanNode<Bitvector>>());
    
    transformation->execute(equivalence);
    std::cout << "End!\n";
    return 0;
}
