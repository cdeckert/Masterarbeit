//
//  main.cpp
//
//  Created by Christian Deckert on 02/02/15.
//

#include <iostream>
#include "TreeGenerator.h"


int main(int argc, const char * argv[]) {
    std::cout << "Start!\n";
    //Reservoir<Plan> * planReservoir = new Reservoir<Plan>(30);
    //planReservoir->get_new_entry();
    TreeGenerator::generate();
    
    return 0;
}
