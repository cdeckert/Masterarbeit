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

template <typename PlanNode_t, typename Bitvector_t> struct EuqivalenceClass;


/**
 * @brief Plan Node iterator
 */
/*template <typename PlanNode_t, typename Bitvector_t>
struct PlanNodeIterator : public std::iterator<std::forward_iterator_tag, PlanNode_t>
{
    typedef PlanNodeIterator<PlanNode_t, Bitvector_t> self_type;
    friend class EuqivalenceClass<PlanNode_t, Bitvector_t>;

    
public:
    PlanNode_t& operator*();
    const self_type& operator++();
    bool operator!=(const self_type& other) const;

private:
    PlanNode_t * _nodePointer;
    PlanNodeIterator(PlanNode_t * nodePoineter) : _nodePointer(nodePoineter){};
};*/



/**
 * @brief
 * Equivalence class is a collection of PlanNode
 */
template <typename PlanNode_t, typename Bitvector_t>
struct EquivalenceClass
{
    
public:
    inline EquivalenceClass(PlanNode_t & aPlanNode) : _first(aPlanNode) {};
    ~EquivalenceClass() { /*delete _first;*/ }
    
    
    inline const Bitvector_t & getRelations()
    {
        return _first.getRelations();
    };
    
    /**
     * @brief push back of plan nodes
     */
    inline void push_back(const PlanNode_t & aPlanNode)
    {
        _last->setNext(_first);
        _last = _last->getNext();
    };
    /**
     * @brief
     */
    inline PlanNode_t & begin()
    {
        return _first;
    };
    
    inline PlanNode_t * end()
    {
        return _last;
    };
    
    
    
    
    
    
private:
    PlanNode_t & _first;
    PlanNode_t * _last;
};


/**
 * @brief custom iterator
 */
template <typename EquivalenceClass_t, typename PlanNode_t>
struct Iterator : public std::iterator<std::forward_iterator_tag, EquivalenceClass_t>
{
    typedef PlanNode_t Node;
public:
    Iterator(Node * node);
    PlanNode_t& operator*() const;
    PlanNode_t* operator->() const;
    
    Iterator& operator++();
    Iterator operator++(int);
    
    friend bool operator == (PlanNode_t a, PlanNode_t b);
    friend bool operator != (PlanNode_t a, PlanNode_t b);
    
    operator Iterator<EquivalenceClass_t, PlanNode_t const>() const;
    
private:
   
    Node * _node;
};






#endif
