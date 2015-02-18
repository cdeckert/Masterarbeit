//
//  EquivalenceClass.h
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 2/16/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#ifndef RuleBasedOptimizer_EquivalenceClass_h
#define RuleBasedOptimizer_EquivalenceClass_h

#include <iterator>






template <typename PlanNode_t, typename Bitvector_t>
struct EquivalenceClass
{
    typedef EquivalenceClass<PlanNode_t, Bitvector_t> self_type;
public:
    EquivalenceClass(){};
private:
    
public:
    struct Iterator : public std::iterator<std::forward_iterator_tag, self_type>
    {
        
    };
};


#endif
