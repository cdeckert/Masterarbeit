//
//  EquivalenceClass.h
//

#ifndef RuleBasedOptimizer_EquivalenceClass_h
#define RuleBasedOptimizer_EquivalenceClass_h

#include <iterator>
#include <ostream>
#include <sstream>
#include <string>


#include "Reservoir.h"


template <typename Bitvector_t, typename PlanNode_t>
class EquivalenceClassIterator
{
    typedef EquivalenceClassIterator self_type;
    
    
public:
    EquivalenceClassIterator(PlanNode_t & aNode) : _node(aNode) {};
    const bool hasNext() { return _node.hasNext(); };
    
    
   
    
    
    

private:
    
    PlanNode_t & _node;
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
    inline Iterator & begin(){ return Iterator(_first); }
    inline Iterator & end(){ return Iterator(_last); }
    inline Bitvector_t & getRelations() { return _relations; };
    void init()
    {
        _first = NULL;
        _last = NULL;
        _relations = NULL;
    };
    
    void push_back(PlanNode_t & aPlanNode)
    {
        if(_first == NULL)
        {
            _first = &aPlanNode;
            _last = &aPlanNode;
        }
        else
        {
            _last->setNext(aPlanNode);
            _last = &aPlanNode;
        }
        
    }
    
    std::ostream & print(std::ostream & os)
    {
        return os;
    };
    
    inline std::ostream & operator<<(std::ostream& os, const EquivalenceClass& x) { return x.print(os); }
    
private:
    Bitvector_t * _relations;
    PlanNode_t * _first;
    PlanNode_t * _last;
};

#endif
