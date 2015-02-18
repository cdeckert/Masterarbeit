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
    inline EquivalenceClass(PlanNode_t & aPlanNode) : _first(aPlanNode) //, _last(aPlanNode)
    {
        _last = &_first;
    };
    inline const Bitvector_t & getRelations()
    {
        return _first.getRelations();
    };
    inline void push(PlanNode_t & aPlanNode)
    {
        _last->setNext(aPlanNode);
        _last = _last->getNext();        
    };
private:
    PlanNode_t & _first;
    PlanNode_t * _last;
};








#endif
