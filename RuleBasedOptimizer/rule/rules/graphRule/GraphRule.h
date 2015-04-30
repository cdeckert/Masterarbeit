//
//  GraphRule.h
//

#ifndef RuleBasedOptimizer_GraphRule_h
#define RuleBasedOptimizer_GraphRule_h


/**
 * @brief Graph Rule
 * @details Rule that creates commutative plan nodes based on a given node
 *
 * @tparam PlanNode_t PlanNode
 * @tparam Operations_t basic operations like join and scan
 */
template <typename PlanNode, typename Operations_t>
class GraphRule : public Rule<PlanNode, Operations_t>
{
    typedef PlanNode PlanNode_t;
    typedef typename PlanNode_t::EquivalenceClass_t EquivalenceClass_t;
    typedef typename EquivalenceClass_t::Iterator EItr;
    typedef typename PlanNode_t::BV Bitvector_t;
    typedef std::unordered_set<Bitvector_t, Hasher<Bitvector_t>> BvSet_t;
    typedef std::unordered_set<Bitvector_t, PlanNode *, Hasher<Bitvector_t>> BVPlanNodeMap_t;
    
    typedef std::unordered_map<Bitvector_t, std::unordered_set<Bitvector_t, Hasher<Bitvector_t>>, Hasher<Bitvector_t>> DPTable_t;
    
public:
    GraphRule(BvSet_t joinEdges) : Rule<PlanNode, Operations_t>(){
        _joinEdges = joinEdges;
    };
    
    void partition(Bitvector_t & input)const;
    
    
    
    
    /**
     * @brief checks whether or not left associativity is applicable
     * @details left associativity is applicable in case the given operation is
     * "JOIN" the left descendant node is a join
     *
     * @param aPlanNode a given plan node
     * @return true in case the rule is applicable
     */
    bool isApplicable(PlanNode & aPlanNode) const override
    {
        // IF is Parent Node
        return aPlanNode.getOperator() == JOIN;
    };
    
    Bitvector_t & merge(Bitvector_t bv1, Bitvector_t bv2) const
    {
        Bitvector_t * js = this->o.get_new_BV(); // =  Bitvector_t();
        js->union_of(bv1, bv2);
        return * js;
    }
    
    std::vector<PlanNode_t *> createTrees(DPTable_t) const
    {
        std::vector<PlanNode_t *> vector;
        return vector;
    }
    
    /**
     * @brief apply graph rule
     */
    PlanNode * apply(PlanNode & aPlanNode) const override
    {
        PlanNode * result = NULL;
        for(PlanNode & js_a : aPlanNode.l())
        {
            for(PlanNode & js_b : aPlanNode.r())
            {
                Bitvector_t & js = merge(js_a.getSignature(), js_b.getSignature());
                this->partition(js);
                for(PlanNode_t * t : this->createTrees(cuts))
                {
                    if(result == NULL) result = t;
                    else result->concat(t);
                }
            }
        }
        return result;
    };
private:
    BvSet_t _joinEdges;
    DPTable_t cuts;
};

template <typename PlanNode, typename Operations_t>
void GraphRule<PlanNode, Operations_t>::partition(Bitvector_t & input)const
{
    if(cuts.count() == 0)
    {
        
    }
};

#endif
