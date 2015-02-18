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
/**
 * @brief custom planNode Iterator
 */
template <typename PlanNode_t>
struct IteratorPlanNode : public std::iterator<std::forward_iterator_tag, PlanNode_t>
{
public:
    IteratorPlanNode(PlanNode_t * node)
    {
        _node = node;
    };
    PlanNode_t& operator*()
    {
        return _node;
    };
    
    const IteratorPlanNode<PlanNode_t>& operator++()
    {
        _node = _node->_next;
        return *this;
    };
    
private:
    PlanNode_t * _node;
};

template <typename PlanNode_t, typename Bitvector_t>
struct EquivalenceClass
{
    typedef EquivalenceClass<PlanNode_t, Bitvector_t> self_type;
    typedef IteratorPlanNode<PlanNode_t> Iterator;

public:
    EquivalenceClass(){};
    Iterator begin(){ return Iterator(_begin);};
    Iterator end(){ return Iterator(_end);};
private:
    PlanNode_t * _begin;
    PlanNode_t * _end;

};


#endif
