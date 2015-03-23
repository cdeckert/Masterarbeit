//
//  Operations.h
//

#ifndef RuleBasedOptimizer_Operations_h
#define RuleBasedOptimizer_Operations_h

/**
 * @brief The operations class offers convinient access to basic operations
 * @details The operations class is used to execute methods like Join or scan.
 * The methods are using reservoirs to reduce the effort for instanciation of
 * new objects.
 * 
 * @tparam Bitvector_t the standard Bitvector
 * @tparam EquivalenceClass_t the equivalence class
 * @tparam PlanNode_t the standard plan Node
 * @tparam u_int an unsigned integer
 */
template <typename PlanNode_t, typename u_int>
class Operations
{
    typedef Operations self_type;
	typedef typename PlanNode_t::Bitvector_t Bitvector_t;
	typedef typename PlanNode_t::EquivalenceClass_t EquivalenceClass_t;
    
public:
    static self_type * exemplar();
    
    Operations()
    {
        reservoirEC = new Reservoir<EquivalenceClass_t>(900);
        reservoirPN = new Reservoir<PlanNode_t>(600);
        bitvectors = new Reservoir<Bitvector_t>(900);
    }
    /**
     * @brief copy constructor
     * @details copy constructor to copy operations
     *
     * @param s a operations instance
     */
    Operations(const Operations &);
    
    /**
     * @brief returns new and initalized bitvector
     * @details returns a new bitvector instance and flips a bit
     * at a specific position
     *
     * @param i position of the flipped bit
     * @return Bitvector
     */
    Bitvector_t * getBitVector(u_int i) const
    {
        Bitvector_t * b = bitvectors->get_new_entry();
        b->set(i);
        return b;
    };
    
    /**
     * @brief creates a equivalence class, which represents a scan operation
     * @details creates a equivalence class, which includes a PlanNode
     * (operation = scan) and a scanned relation
     *
     * @param i the scanned relation
     * @return [description]
     */
    EquivalenceClass_t & scan(u_int i) const
    {
        Bitvector_t * b = getBitVector(i);
        
        EquivalenceClass_t & eqN = * reservoirEC->get_new_entry();
        eqN.setRelations(*b);
        PlanNode_t & t = * reservoirPN->get_new_entry();
        t.set(SCAN, &eqN, NULL);
        EquivalenceClass_t & eq = * reservoirEC->get_new_entry();
        
        eq.push_back(t);
        return eq;
    }
    
    
    /**
     * @brief Creates a planNode, which represents a join operation
     * to initalize the predicate, please use the "on" method
     *
     * @param e1 Left relation
     * @param e2 Right relation
     *
     * @return plan node with a single plan
     */
    PlanNode_t & joinPN(EquivalenceClass_t & e1, EquivalenceClass_t & e2) const
    {
        PlanNode_t & t = * reservoirPN->get_new_entry();
        t.set(JOIN, &e1, &e2);
        return t;
    }
    
    
    /**
     * @brief Creates a Equivalence Class which represents a join operation
     * @details The Equivalence class is initalized with a simple plan (operation Join)
     * to initalize the predicate, please use the "on" method
     *
     * @param e1 Left relation
     * @param e2 Right relation
     *
     * @return equivalence class with a single plan
     */
    EquivalenceClass_t & join(EquivalenceClass_t & e1, EquivalenceClass_t & e2, Bitvector_t & joinOnRelation) const
    {
		e1.setNeighbors(joinOnRelation);
		e2.setNeighbors(joinOnRelation);

		PlanNode_t & t = joinPN(e1, e2);
        EquivalenceClass_t  & eq = * reservoirEC->get_new_entry();
        eq.push_back(t);
        return eq;
    }
private:
    Reservoir<EquivalenceClass_t> * reservoirEC;
    Reservoir<Bitvector_t> * bitvectors;
    Reservoir<PlanNode_t> * reservoirPN = new Reservoir<PlanNode_t>(600);
    static self_type * instance;
    
};

template <typename PlanNode_t, typename u_int>
Operations<PlanNode_t, u_int> * Operations<PlanNode_t, u_int>::instance;


template <typename PlanNode_t, typename u_int>
Operations<PlanNode_t, u_int> * Operations<PlanNode_t, u_int>::exemplar()
{
    if(instance == NULL)
    {
        instance = new Operations();
    }
    return instance;
}







#endif
