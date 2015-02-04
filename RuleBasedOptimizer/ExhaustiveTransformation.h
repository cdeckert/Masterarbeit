//
//  ExhaustiveTransformation.h
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 03/02/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#ifndef __RuleBasedOptimizer__ExhaustiveTransformation__
#define __RuleBasedOptimizer__ExhaustiveTransformation__

#include <stdio.h>
#include <unordered_set>


template <typename Tree>
class ExhaustiveTransformation {
    std::unordered_set<Tree> done;
    std::unordered_set<Tree> toDo;
    
public:
    ExhaustiveTransformation();
    Tree * execute(Tree);
    std::unordered_set<Tree> applyTransformations(Tree);
};


#endif /* defined(__RuleBasedOptimizer__ExhaustiveTransformation__) */
