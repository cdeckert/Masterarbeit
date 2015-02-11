//
//  ExhaustiveTransformation.cpp
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 04/02/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#include "ExhaustiveTransformation.h"

Plan * ExhaustiveTransformation::execute(Equivalence* equivalence)
{
    toDo.push_back(equivalence);
    /*while (!toDo.empty()) {
        //Equivalence * e = toDo.pop_back();
        done.push_back(e);
        std::vector<Equivalence *> trees = this->applyTransormation(e);
        for(Equivalence * e : trees)
        {
            if(!done.contains(e) && toDo.contains(e))
            {
                toDo.push_back(e);
            }
        }
        
    }*/
    return NULL;
}

/*std::vector<Equivalence> ExhaustiveTransformation::applyTransormation(Equivalence * e)
{
    return NULL;
    //for()
}*/