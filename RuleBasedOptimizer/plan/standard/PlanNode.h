//
//  PlanNode.h
//

#ifndef RuleBasedOptimizer_PlanNode_h
#define RuleBasedOptimizer_PlanNode_h

#include "Operator.h"
#include "EquivalenceClass.h"


template <typename Bitvector_t>
class PlanNode {
    typedef PlanNode self_type;
    typedef EquivalenceClass<Bitvector_t, self_type> EquivalenceClass_t;
public:
    PlanNode(){ init(); };
    self_type * getNext() const { return _next; }
    void setNext(self_type & aNode) {_next = &aNode; };
    Bitvector_t getSignature() { return _left->getRelations(); }
    
    void set(Operator anOperator, EquivalenceClass_t & aLeftEC, EquivalenceClass_t & aRightEC)
    {
        _op = anOperator;
        _left = &aLeftEC;
        _right = &aRightEC;
    };
    
private:
    void init()
    {
        _next = NULL;
        _left = NULL;
        _right = NULL;
        //_relations = new Bitvector_t(0);
    };
    Operator _op;
    self_type * _next;
    EquivalenceClass_t * _left;
    EquivalenceClass_t * _right;
    Bitvector_t * _relations;
};



#endif
