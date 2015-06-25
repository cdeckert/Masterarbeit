//
//  GraphRule.h
//

#ifndef RuleBasedOptimizer_GraphRule_h
#define RuleBasedOptimizer_GraphRule_h

#define ELPP_STL_LOGGING
#define ELPP_LOG_UNORDERED_SET
#define TESTING_YES

#include "easylogging++.h"
#include <list>
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
	//typedef std::unordered_set<Bitvector_t, Hasher<Bitvector_t>> BvSet_t;
	typedef std::unordered_set<Bitvector_t, PlanNode *, Hasher<Bitvector_t>> BVPlanNodeMap_t;
	typedef typename Bitvector_t::IteratorElement BVIter;
	typedef std::unordered_map<Bitvector_t, std::unordered_set<Bitvector_t, Hasher<Bitvector_t>>, Hasher<Bitvector_t>> DPTable_t;
	typedef typename EquivalenceClass_t::Iterator ECItr_t;


    struct partition_res
    {
    public:
        Bitvector_t _left;
        Bitvector_t _right;
    };
    
    typedef std::list<partition_res> BvSet_t;
public:


	GraphRule() : Rule<PlanNode, Operations_t>() {};
	GraphRule(std::unordered_set<Bitvector_t, Hasher<Bitvector_t>> joinEdges) : Rule<PlanNode, Operations_t>()
	{
		_joinEdges = joinEdges;
	};

	std::string getName() const override
	{
		return "graphRule";
	}

	/**
	 * @brief checks whether or not left associativity is applicable
	 * @details left associativity is applicable in case the given operation is
	 * "JOIN" the left descendant node is a join
	 *
	 * @param aPlanNode a given plan node
	 * @return true in case the rule is applicable
	 */
	bool isApplicable(PlanNode &aPlanNode) const override
	{
		// IF is Parent Node
		return aPlanNode.getOperator() == JOIN && !aPlanNode._explored;
	};

	bool isApplicable(PlanNode &aPlanNode, PlanNode_t &left, PlanNode_t &right) const override
	{
		// IF is Parent Node
		return aPlanNode.getOperator() == JOIN && !aPlanNode._explored;
	};


	/**
	 * @brief apply graph rule
	 */
	PlanNode *apply(PlanNode &aPlanNode) const override
	{
		Bitvector_t js = merge(aPlanNode.l().getRelations(), aPlanNode.r().getRelations());
		BvSet_t partition = this->partition(js);
		EquivalenceClass_t *e = this->createTrees(partition, js);
		return e->getFirst();
	};

	PlanNode *apply(PlanNode &aPlanNode, PlanNode &left, PlanNode &right) const override
	{
		Bitvector_t js = merge(aPlanNode.l().getRelations(), aPlanNode.r().getRelations());
		BvSet_t partition = this->partition(js);
		EquivalenceClass_t *e = this->createTrees(partition, js);
        aPlanNode._explored = true;
		return e->getFirst();
	};


private:
	/**
	 * @brief [brief description]
	 * @details [long description]
	 *
	 * @param input [description]
	 * @return [description]
	 */
	BvSet_t partition(Bitvector_t &input) const;

	std::unordered_set<Bitvector_t, Hasher<Bitvector_t>> getConnectedPars(Bitvector_t s, Bitvector_t c, Bitvector_t);
    std::list<Bitvector_t> getConnectedParts(Bitvector_t S, Bitvector_t C, Bitvector_t T) const;
	Bitvector_t getNeighbors(Bitvector_t relations, Bitvector_t s) const;
	void MinCutConservative(Bitvector_t &subSetOfRelations, Bitvector_t &connectedRelations, Bitvector_t &excluded, BvSet_t & partitions) const;
	Bitvector_t merge(Bitvector_t bv1, Bitvector_t bv2) const
	{
		Bitvector_t js;
		js.union_of(bv1, bv2);
		return js;
	}
	EquivalenceClass_t *createTrees(BvSet_t partition, Bitvector_t js) const;

	std::unordered_set<Bitvector_t, Hasher<Bitvector_t>> _joinEdges;
	bool _isApplicable = true;
};



//
// Implemenetation
//


template <typename PlanNode, typename Operations_t>
void
GraphRule<PlanNode, Operations_t>::MinCutConservative(Bitvector_t &s, Bitvector_t &c, Bitvector_t &x, BvSet_t & partitions) const
{
    /*std::cout << "c:" << c << std::endl;
    std::cout << "x:" << x << std::endl;
    std::cout << "c.disjoint(s)" << c.disjoint(s) << std::endl;*/
    if(c == s) //  || c.disjoint(s))
    {
        //return;
    }
    
    if(!c.is_empty())
    {
        partition_res part;
        part._left = c;
        part._right = s;
        part._right.set_difference(c);
        //std::cout <<part._left << ":" <<part._right << std::endl;
        partitions.push_back(part);
    }
    
    Bitvector_t x_prim(x);
    Bitvector_t neigh_no_x(getNeighbors(c,s));
    if(c.is_empty())
    {
        neigh_no_x = s.lowest_bit();
    }
    neigh_no_x.intersect_with(s).set_difference(x);
    
    for (typename Bitvector_t::IteratorBit v_iter = neigh_no_x.beginBit(); v_iter != neigh_no_x.endBit(); ++v_iter) {
        Bitvector_t v(*v_iter);
        
        std::list<Bitvector_t> bcc;
        bcc = getConnectedParts(s, Bitvector_t(c).union_with(v), v);
        typename std::list<Bitvector_t>::iterator list_iter;
        
        x_prim.union_with(v);
        for (list_iter = bcc.begin(); list_iter != bcc.end(); ++list_iter) {
            MinCutConservative(s, Bitvector_t(s).set_difference(*list_iter), x_prim, partitions);
        }
        
       
    }

};

template <typename PlanNode, typename Operations_t>
typename GraphRule<PlanNode, Operations_t>::BvSet_t
GraphRule<PlanNode, Operations_t>::partition(Bitvector_t &input)const
{
	Bitvector_t b;
    BvSet_t bv;
    MinCutConservative(input, b, b, bv);
    return bv;
};

template <typename PlanNode, typename Operations_t>
typename GraphRule<PlanNode, Operations_t>::EquivalenceClass_t *
GraphRule<PlanNode, Operations_t>::createTrees(BvSet_t partition, Bitvector_t js) const
{
	EquivalenceClass_t *eq = new EquivalenceClass_t();
	for (partition_res t : partition)
	{
        PlanNode & p = this->o.joinPN(* this->o.scan(t._left), * this->o.scan(t._right));
        p._explored = true;
        eq->push_back(p);
        /*std::cout << "T" << &t << std::endl;
        if (t == js && t.size() == 1)
        {
            return this->o.scan(t);
        }
			else
			{
				if (partition.count(js.without(t)) > 0)
				{
					EquivalenceClass_t &left = *createTrees(partition, t);

					std::cout << t << std::endl;
					EquivalenceClass_t &right = *createTrees(partition, js.without(t));

					if (left.getRelations().size() > 0 && right.getRelations().size() > 0)
					{
						std::cout << "l" << left.getRelations() << std::endl;
						std::cout << "r" << right.getRelations() << std::endl;
						EquivalenceClass_t * p = this->o.join(left, right);

						p->getFirst()->print();
						eq->concat(p);
					}
				}
			}
		}*/
	}
	return eq;
};


template <typename PlanNode, typename Operations_t>
std::list<typename GraphRule<PlanNode, Operations_t>::Bitvector_t>  GraphRule<PlanNode, Operations_t>::getConnectedParts(Bitvector_t S, Bitvector_t C, Bitvector_t T) const
{
    std::list<Bitvector_t> O;
	Bitvector_t D, N, U, L_new;
    N = getNeighbors(T, S);
    N.intersect_with(S);
    N = N.without(C);
	if (N.size() <= 1)
	{
		Bitvector_t b = S.without(C);
		O.push_back(b);
		O.push_back(C);
		//return O;
	}
    
    
	for (unsigned int i = 0; i < N.capacity(); ++i)
	{
		Bitvector_t L;
		if (N.test(i))
		{
			L_new.set(i);
			U = N.without(L_new);
			while (L != L_new && U.is_not_empty())
			{
				D = L_new.without(L);
				L = L_new;
				L_new.union_with(getNeighbors(D, S).without(C));
				U = U.without(L_new);
			}
			if (U.is_not_empty())
			{
                O.push_back(S.without(C));
                O.push_back(C); //, C});
			}
			U = N.without(L);
			while (U.is_not_empty())
			{
				L.reset();
				for (unsigned int i = 0; i < U.capacity(); ++i)
				{
					L_new.reset();
					if (U.test(i))
					{
						L_new.set(i);
						while (L != L_new)
						{
							D = L_new.without(L);
							L = L_new;
							L_new.union_with(getNeighbors(D, S).without(C));
						}
                        O.push_back(L);
                        O.push_back(D); // , D});
						U = U.without(L);
					}

				}
			}

		}
	}
	return O;
};



template <typename PlanNode, typename Operations_t>
typename GraphRule<PlanNode, Operations_t>::Bitvector_t GraphRule<PlanNode, Operations_t>::getNeighbors(Bitvector_t relations, Bitvector_t s) const
{
    
    Bitvector_t result;
    result.reset();
	if (relations.is_empty())
	{

		for (unsigned int i = 0; i < s.capacity(); ++i)
		{
			if (s.test(i)) return result.set(i);
		}

	}
	else
	{

		for (unsigned int i = 0; i < relations.capacity(); ++i)
		{
			if (relations.test(i))
			{
				Bitvector_t r; r.set(i);
				for (Bitvector_t aJoinEdge : _joinEdges)
				{
					if (aJoinEdge.contains(r))
					{
						result.union_with(~r & aJoinEdge);
						break;
					}
				}
			}

		}
	}
	//LOG(INFO) << "getNeighbors( relations: " << relations << ", s: " << s << ") : " << result;
	return result;
}


#endif
