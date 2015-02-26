//
//  Operations.h
//

#ifndef RuleBasedOptimizer_Operations_h
#define RuleBasedOptimizer_Operations_h

template <typename Bitvector_t, typename EquivalenceClass_t, typename PlanNode_t, typename u_int>
class Operations {
    
public:
    Bitvector_t * getBitVector(u_int i){
        Bitvector_t * b = new Bitvector_t();
        b->set(i);
        return b;
    };
    EquivalenceClass_t * scan(u_int i)
    {
        Bitvector_t * b = getBitVector(i);
        EquivalenceClass_t *eq = new EquivalenceClass_t(); //reservoirEC->get_new_entry();
        eq->setRelations(*b);
        PlanNode_t * t = new PlanNode_t(); //reservoirPN->get_new_entry();
        t->set(SCAN, eq);
        eq->push_back(t);
        return eq;
    }
    
    EquivalenceClass_t * join(EquivalenceClass_t * e1, EquivalenceClass_t * e2)
    {
        PlanNode_t * t = new PlanNode_t(); // reservoirPN->get_new_entry();
        t->set(JOIN, e1, e2);
        EquivalenceClass_t * eq = new EquivalenceClass_t(); //  reservoirEC->get_new_entry();
        eq->push_back(t);
        return eq;
    }
    
    
};


#endif
