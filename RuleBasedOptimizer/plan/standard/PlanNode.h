//
//  PlanNode.h
//

#ifndef RuleBasedOptimizer_PlanNode_h
#define RuleBasedOptimizer_PlanNode_h

#include "Operator.h"
#include "EquivalenceClass.h"

/**
 * @brief Equivalence Class is a collection of equivalent PlanNodes
 */
template <typename Bitvector_t>
struct PlanNode
{
    typedef PlanNode<Bitvector_t> self_type;
    typedef EquivalenceClass<self_type, Bitvector_t> EquivalenceClass_t;


public:
    PlanNode(Operator op, Bitvector_t & left, Bitvector_t & right):
    _op(op),
    _left(left),
    _right(right)
    
    {
        _leftEC = nullptr;
        _rightEC = nullptr;
        cacheRelations();
    };
    
    
    PlanNode(Operator op, EquivalenceClass_t & left, EquivalenceClass_t & right) :
    _op(op),
    _left(left.getRelations()),
    _right(right.getRelations())
    {
        _leftEC = left;
        _rightEC = right;
        cacheRelations();
    };
    
    PlanNode(Operator op, Bitvector_t & left, EquivalenceClass_t & right) :
    _op(op),
    _left(left),
    _right(right.getRelations())
    {
        _rightEC = right;
        cacheRelations();
    };
    
    PlanNode(Operator op, EquivalenceClass_t & left, Bitvector_t & right) :
    _op(op),
    _left(left.getRelations()),
    _right(right)
    {
        _leftEC = left;
        cacheRelations();
    };
    
    inline Bitvector_t & getRelations()
    {
        return _relations;
    }
    
    
    

private:
    const Operator _op;
    Bitvector_t & _left;
    Bitvector_t &  _right;
    
    Bitvector_t _relations;
    
    EquivalenceClass_t * _leftEC;
    EquivalenceClass_t * _rightEC;
    
    /**
     * @brief caches relations from left and right
     */
    void cacheRelations()
    {
        _relations += _left;
        _relations += _right;
    };

};




#endif
