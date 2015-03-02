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
    inline Iterator begin()const { return Iterator(*_first); }
    inline Iterator & end() const { return Iterator(*_last); }
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
    
    void push_back(PlanNode_t & aPlanNode)
    {
        if(_first == NULL)
        {
            _first = &aPlanNode;
            _last = &aPlanNode;
            _relations += _first->getRelations();
        }
        else
        {
           
            _last->setNext(&aPlanNode);
            _last = &aPlanNode;
            _relations += _last->getSignature();
        }
        
    }
    
    std::ostream & print(std::ostream & os) const
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
    
    std::ostream & printEndl(std::ostream & os) const
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
    
    self_type & on(unsigned int left, unsigned right)
    {
        _first->on(left, right);
        return *this;
    }
    
    u_int getSize() const
    {
                
        
        u_int size = 0;
        for(Iterator itr = begin(); itr.isOK(); ++itr)
        {
            size += itr.node()->getSize();
        }
        
        
        return size;
    }
    
    u_int getCount() const
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
    
    Operator getOperator() const
    {
        return begin()->getOperator();
    }
    
    self_type & getLeft() const
    {
        return begin()->getLeft();
    }
    
    self_type & getRight() const
    {
        return begin()->getRight();
    }
    
    unsigned int getLeftAttribute() const
    {
        return begin()->getLeftAttribute();
    }
    
    unsigned int getRightAttribute() const
    {
        return begin()->getRightAttribute();
    }
    
    
        
private:
    Bitvector_t _relations;
    PlanNode_t * _first;
    PlanNode_t * _last;
    
    
    bool hasPlanNodes() const
    {
        return _first != NULL;
    }
};

#endif
