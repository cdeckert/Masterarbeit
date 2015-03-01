//
//  Operations.h
//

#ifndef RuleBasedOptimizer_Operations_h
#define RuleBasedOptimizer_Operations_h

template <typename Bitvector_t, typename EquivalenceClass_t, typename PlanNode_t, typename u_int>
class Operations
{
    typedef Operations self_type;
public:
    static self_type * exemplar();
    Operations()
    {
        reservoirEC = new Reservoir<EquivalenceClass_t>(900);
        reservoirPN = new Reservoir<PlanNode_t>(600);
        bitvectors = new Reservoir<Bitvector_t>(900);
    }
    
    Operations(const Operations &);
    
    Bitvector_t * getBitVector(u_int i) const
    {
        Bitvector_t * b = new Bitvector_t();
        b->set(i);
        return b;
    }
    ;
    EquivalenceClass_t & scan(u_int i) const
    {
        Bitvector_t * b = getBitVector(i);
        
        EquivalenceClass_t *eq = reservoirEC->get_new_entry();
        eq->setRelations(*b);
        PlanNode_t * t = reservoirPN->get_new_entry();
        t->set(SCAN, eq, NULL);
        eq = reservoirEC->get_new_entry();
        
        eq->push_back(t);
        return * eq;
    }
    
    EquivalenceClass_t & join(EquivalenceClass_t & e1, EquivalenceClass_t & e2) const
    {
        PlanNode_t * t = reservoirPN->get_new_entry();
        t->set(JOIN, &e1, &e2);
        EquivalenceClass_t  & eq = * reservoirEC->get_new_entry();
        eq.push_back(t);
        return eq;
    }
    
    PlanNode_t & joinPN(EquivalenceClass_t & e1, EquivalenceClass_t & e2)
    {
        PlanNode_t & t = * reservoirPN->get_new_entry();
        t.set(JOIN, &e1, &e2);
        return t;
    }
private:
    Reservoir<EquivalenceClass_t> * reservoirEC;
    Reservoir<Bitvector_t> * bitvectors;
    Reservoir<PlanNode_t> * reservoirPN = new Reservoir<PlanNode_t>(600);
    static self_type * instance;
    
};

template <typename Bitvector_t, typename EquivalenceClass_t, typename PlanNode_t, typename u_int>
Operations<Bitvector_t, EquivalenceClass_t, PlanNode_t, u_int> * Operations<Bitvector_t, EquivalenceClass_t, PlanNode_t, u_int>::instance;

template <typename Bitvector_t, typename EquivalenceClass_t, typename PlanNode_t, typename u_int>
Operations<Bitvector_t, EquivalenceClass_t, PlanNode_t, u_int> * Operations<Bitvector_t, EquivalenceClass_t, PlanNode_t, u_int>::exemplar()
{
    if(instance == NULL)
    {
        instance = new Operations();
    }
    return instance;
}







#endif
