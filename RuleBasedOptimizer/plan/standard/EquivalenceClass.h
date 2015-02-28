//
//  EquivalenceClass.h
//

#ifndef RuleBasedOptimizer_EquivalenceClass_h
#define RuleBasedOptimizer_EquivalenceClass_h

#include <iterator>
#include <ostream>
#include <sstream>
#include <string>
#include <iostream>


#include "Reservoir.h"


template <typename Bitvector_t, typename PlanNode_t>
class EquivalenceClassIterator
{
    typedef EquivalenceClassIterator self_type;
    
    
public:
    EquivalenceClassIterator(PlanNode_t & aNode){ _node = &aNode; };
    const bool hasNext() { return _node->hasNext(); };
    const bool isOK() { return _node != NULL; };
    PlanNode_t * node(){ return _node; };
    
    
    self_type& operator++()
    {
        _node = _node->getNext();
        return *this;
    };
    
    inline PlanNode_t * operator->() const
    {
        return _node;
    };
    
    
    
    

private:
    
    PlanNode_t * _node;
};




template <typename Bitvector_t , typename PlanNode_t>
struct EquivalenceClass
{
    typedef EquivalenceClass self_type;
    typedef EquivalenceClassIterator<Bitvector_t, PlanNode_t> Iterator;
    typedef Reservoir<self_type> Reservoir_t;
    
    friend Iterator;
    
public:
    EquivalenceClass() { init(); };
    inline Iterator begin(){ return Iterator(*_first); }
    inline Iterator & end(){ return Iterator(*_last); }
    inline Bitvector_t & getRelations() { return _relations; };
    void init()
    {
        _first = NULL;
        _last = NULL;
    };
    
    void setRelations(Bitvector_t & aRelations)
    {
        _relations+=aRelations;
    }
    
    void push_back(PlanNode_t * aPlanNode)
    {
        if(_first == NULL)
        {
            _first = aPlanNode;
            _last = aPlanNode;
            _relations += _first->getRelations();
        }
        else
        {
           
            _last->setNext(aPlanNode);
            _last = aPlanNode;
            _relations += _last->getSignature();
        }
        
    }
    
    std::ostream & print(std::ostream & os)
    {
        if(hasPlanNodes())
        {
            for(Iterator itr = begin(); itr.isOK(); ++itr)
            {
                itr.node()->print(os);
            }
        }
        else
        {
            _relations.print2(os);
            /*os << "[";
            _relations.print(os);
            os << "]";*/
        }
        
        return os;
    };
    
    std::ostream & printEndl(std::ostream & os)
    {
        int i = 0;
        if(hasPlanNodes())
        {
            for(Iterator itr = begin(); itr.isOK(); ++itr)
            {
                i++;
                os << i << ": ";
                itr.node()->print(os) << std::endl;
            }
        }
        else
        {
            _relations.print2(os);
            /*os << "[";
             _relations.print(os);
             os << "]";*/
        }
        
        return os;
    };
    
    u_int getSize()
    {
                
        
        u_int size = 0;
        for(Iterator itr = begin(); itr.isOK(); ++itr)
        {
            size += itr.node()->getSize();
        }
        
        
        return size;
    }
    
    u_int getCount()
    {
        u_int count = 0;
        for(Iterator itr = begin(); itr.isOK(); ++itr)
        {
            count += itr.node().getCount();
        }
        return count;
    }
    
    Bitvector_t & getSignature()
    {
        return _relations;
    }
    
        
private:
    Bitvector_t _relations;
    PlanNode_t * _first;
    PlanNode_t * _last;
    
    
    bool hasPlanNodes()
    {
        return _first != NULL;
    }
};

#endif
