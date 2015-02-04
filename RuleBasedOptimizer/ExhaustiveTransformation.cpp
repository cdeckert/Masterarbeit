//
//  ExhaustiveTransformation.cpp
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 03/02/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#include "ExhaustiveTransformation.h"

template <typename Tree>
Tree * ExhaustiveTransformation<Tree>::execute(Tree tree)
{
    this->toDo.insert(tree);
    while(!toDo.empty())
    {
        Tree* anArbitartyJoinTree = this->toDo.any();
        this->done.insert(anArbitartyJoinTree);
        for(Tree t : this->applyTransformations(anArbitartyJoinTree))
        {
            if(!this->toDo.contains(t) && !this->done.contains(t))
            {
                this->toDo.insert(t);
            }
        }
        
    }
    return new Tree();
}


template <typename Tree>
std::unordered_set<Tree> ExhaustiveTransformation<Tree>::applyTransformations(Tree tree) {
    std::unordered_set<Tree> trees;
    for(Tree subtree : tree.getSubTrees())
    {
        if(subtree.isCommutativityAllowed())
        {
            trees.insert(subtree.applyCommutativity().returnTree());
        }
        if(subtree.isRightAssosiativityAllowed())
        {
            trees.insert(subtree.applyRightAssosiativity().returnTree());
        }
        if(subtree.isLeftAssosiativityAllowed())
        {
            trees.insert(subtree.applyLeftAssosiativity().returnTree());

        }
    }
    return trees;
}
