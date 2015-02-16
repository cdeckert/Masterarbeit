//
//  EquivalenceClass.h
//
//

#ifndef __RuleBasedOptimizer__EquivalenceClass__
#define __RuleBasedOptimizer__EquivalenceClass__

#include <stdio.h>
#include <unordered_set>
#include <iterator>



template <typename Bitvector, typename PlanNode>
struct EquivalenceClass
{
    typedef EquivalenceClass self_type;
    typedef PlanNode *iterator;
    typedef PlanNode valueType;
    
public:
    struct Iterator : public std::iterator<std::input_iterator_tag, PlanNode>
    {
        
    private:
        PlanNode * _current;
    };
    EquivalenceClass();
    EquivalenceClass( PlanNode &);
    PlanNode * begin() const;
    PlanNode * end() const;
    void push(PlanNode&);
    
    bool empty();
    
    unsigned int getSize();
    

private:
    void init();
    Bitvector _relations;
    const PlanNode * _begin;
    PlanNode * _current;
    PlanNode * _end;
    unsigned int _size;
    
    
    
    
};


template <typename Bitvector, typename PlanNode>
void EquivalenceClass<Bitvector, PlanNode>::init()
{
    this->_relations = Bitvector();
    _size = 0;
}

/*template <typename Bitvector, typename PlanNode>
EquivalenceClass<Bitvector, PlanNode>::EquivalenceClass(const PlanNode & planNode)
{
    _relations = planNode.getRelations();
    _begin = * planNode;
    _current = _begin;
    _end = _begin;

}*/

template <typename Bitvector, typename PlanNode>
EquivalenceClass<Bitvector, PlanNode>::EquivalenceClass()
{
    init();
}

template <typename Bitvector, typename PlanNode>
void EquivalenceClass<Bitvector, PlanNode>::push(PlanNode & planNode)
{
    if(_size == 0)
    {
        _begin = &planNode;
        //_end = &planNode;
        //_current = &planNode;
    }
    else
    {
        _end->_next = &planNode;
    }
    ++_size;
    
    //_end = _end->_next;
}

template <typename Bitvector, typename PlanNode>
PlanNode * EquivalenceClass<Bitvector, PlanNode>::begin() const
{
    return _begin;
}

template <typename Bitvector, typename PlanNode>
PlanNode * EquivalenceClass<Bitvector, PlanNode>::end() const
{
    return _end;
}

template <typename Bitvector, typename PlanNode>
unsigned int EquivalenceClass<Bitvector, PlanNode>::getSize()
{
    return _size;
}








// Implementation

#endif /* defined(__RuleBasedOptimizer__EquivalenceClass__) */
