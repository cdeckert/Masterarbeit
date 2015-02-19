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
        _leftEC = NULL;
        _rightEC = NULL;
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
        _leftEC = NULL;
        _rightEC = &right;
        cacheRelations();
    };
    
    PlanNode(Operator op, EquivalenceClass_t & left, Bitvector_t & right) :
    _op(op),
    _left(left.getRelations()),
    _right(right)
    {
        _rightEC = NULL;
        _leftEC = left;
        cacheRelations();
    };
    
    inline Bitvector_t & getRelations()
    {
        return _relations;
    }
    
    inline std::ostream& print(std::ostream& os) const
    {
        os << _op << "(";
        if(_leftEC == NULL)
        {
            os << _left;
        }
        else
        {
            _leftEC->printFirst(os);
        }
        os << ",";
        if(_rightEC == NULL)
        {
            os << _right;
        }
        else
        {
            _rightEC->printFirst(os);
        }
        os << ")";
                      
        return os;
    }

public:
    self_type * _next;
    
    

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
