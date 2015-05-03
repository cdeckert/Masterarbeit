//
//  GraphRule.h
//

#ifndef RuleBasedOptimizer_GraphRule_h
#define RuleBasedOptimizer_GraphRule_h

//#include "MinCutConservative.h"

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
    
    
    typedef typename EquivalenceClass_t::Iterator ECItr_t;
    
public:
    GraphRule(BvSet_t joinEdges) : Rule<PlanNode, Operations_t>(){
        _joinEdges = joinEdges;
    };
    
    void partition(Bitvector_t & input)const;
    
    std::unordered_set<Bitvector_t, Hasher<Bitvector_t>> getConnectedPars(Bitvector_t s, Bitvector_t c, Bitvector_t);
    
    /*BvSet_t MinCutConservative(Bitvector_t & s, Bitvector_t & c, Bitvector_t & x) const
    {
        BvSet_t result;
        if(c == s) return result;
        if(c.log2() != 0) result.insert({{c}});
        Bitvector_t x_new = x;
        Bitvector_t itr;
        itr.union_of(c, s);
        itr.set_difference(x);
        for(Bitvector_t v : itr)
        {
            std::cout << v;
            BvSet_t o;
            Bitvector_t inputCut;
            inputCut.union_of(c, v);
            o = getConnectedParts(s, inputCut, v);
            for(Bitvector_t o_i : o)
            {
                
                
                BvSet_t r = MinCutConservative(s, inputCut, v);
                result.insert(r.begin(), r.end());
            }
            //std::unordered_set<Bitvector_t> o; // = getConnectedParts();
        }
        return result;
    }*/
    
    Bitvector_t neighbor(Bitvector_t & t)
    {
        return t;
    }
    
    BvSet_t getConnectedParts(Bitvector_t S, Bitvector_t C, Bitvector_t T) const
    {
        BvSet_t result;
        /*Bitvector_t N; N.intersection_of(neighbor(T), C);
        if(N.size() <= 1)
        {
            return {intersection_of(S, C)};
        }
        Bitvector_t L;
        for(Bitvector_t L_new : N)
        {
            Bitvector_t U;  U.intersection_of(N, L_new);
            while(L != L_new && !U.isEmpty())
            {
                Bitvector_t D; D.intersection_of(L_new, L);
                L = L_new;
                L_new.union_of(L_new, neighbor(D));
                L_new.intersection_of(L_new, C);
                U.intersection_of(U, L_new);
                
            }
        }*/
        return result;
    }
    
    Bitvector_t getNeighbors(Bitvector_t relations) const
    {
        Bitvector_t result;
        for(Bitvector_t r : relations)
        {
            for(Bitvector_t aJoinEdge : _joinEdges)
            {
                if(aJoinEdge.contains(r))
                {
                    result.union_with(~r & aJoinEdge);
                    break;
                }
            }
        }
        for(Bitvector_t b : result)
        {
            std::cout <<  "BITVECTOR: "<< b.log2() << ",";
        }
        return result;
    }
    
    
    BvSet_t MinCutConservative(Bitvector_t & subSetOfRelations, Bitvector_t & connectedRelations, Bitvector_t & excluded) const
    {
        BvSet_t result;
        
        if(connectedRelations == subSetOfRelations)
        {
            return result;
        }
        if(!connectedRelations.is_empty())
        {
            result.insert({connectedRelations});
            return result;
        }
        Bitvector_t excluded_new = excluded;
        Bitvector_t neighborhood;
        if(connectedRelations.is_empty())
        {
            neighborhood = subSetOfRelations;
        }
        else
        {
            neighborhood = connectedRelations;
        }
        neighborhood.intersect_with(excluded);
        for(Bitvector_t v : neighborhood)
        {
            BvSet_t o = getConnectedParts(subSetOfRelations, connectedRelations & v, v);
        }
        
        
        Bitvector_t b = getNeighbors(subSetOfRelations);
        /*if(c == s)
        {
            return result;
        }*/
        /*if(c.size() > 0)
        {
            result.insert(c.begin(), c.end());
        }
        BvSet_t x_new;
        x_new.insert(x.begin(), x.end());*/
        /*for(Bitvector_t c_new : c)
        {
            for(Bitvector_t x_new : x)
            {
                Bitvector_t v = c_new.set_to_difference(c_new, x_new);
                BvSet_t c_new2 = c;
                c_new2.insert({v});
                BvSet_t o = getConnectedParts(s, c_new2, {v});
                for(Bitvector_t o_new : o)
                {
                    BvSet_t new_c;
                    new_c.insert({o_new});
                    BvSet_t r = MinCutConservative(s, new_c, x_new);
                    result.insert(r.begin(), r.end());
                    x_new.set_union(v);
                }
            }
        }*/
        return result;
    }
    
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
        std::cout << "APPLY" << std::endl;
        PlanNode * result = NULL;
        std::cout << (aPlanNode.l().begin() != aPlanNode.l().end());
        std::cout.flush();
        for(ECItr_t itr_a = aPlanNode.l().begin(); itr_a.isOK(); ++itr_a)
        {
            PlanNode_t & js_a = * itr_a;
            std::cout << "l" << js_a.getSignature();
            for(ECItr_t itr_b = aPlanNode.r().begin(); itr_b.isOK(); ++itr_b)
            {
                PlanNode_t js_b = * itr_b;
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
    BvSet_t empty;
    empty.insert(Bitvector_t());
    Bitvector_t b;
    MinCutConservative(input, b, b);
};



/*template <typename PlanNode, typename Operations_t>
std::unordered_set<Bitvector_t, Hasher<Bitvector_t>> GraphRule<PlanNode, Operations_t>::getConnectedPars(Bitvector_t s, Bitvector_t c, Bitvector_t)
{
    std::unordered_set<Bitvector_t, Hasher<Bitvector_t>> result;
    
    return result;
}*/

#endif
