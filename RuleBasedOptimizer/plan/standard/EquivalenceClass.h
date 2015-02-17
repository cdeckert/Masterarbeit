//
//  EquivalenceClass.h
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 2/16/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#ifndef RuleBasedOptimizer_EquivalenceClass_h
#define RuleBasedOptimizer_EquivalenceClass_h


template <typename PlanNode_t, typename Bitvector_t>
struct EquivalenceClass
{
    
public:
    inline EquivalenceClass(PlanNode_t & planNode) : _first(planNode){};
    inline const Bitvector_t & getRelations() { return _first.getRelations(); }
private:
    PlanNode_t & _first;
    PlanNode_t * _last;
};








#endif
