//
//  GraphRule.h
//

#ifndef RuleBasedOptimizer_GraphRule_h
#define RuleBasedOptimizer_GraphRule_h

#define ELPP_STL_LOGGING
#define ELPP_LOG_UNORDERED_SET
#define TESTING_YES

//#include "MinCutConservative.h"
#include "easylogging++.h"
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
	typedef typename Bitvector_t::IteratorElement BVIter;
	typedef std::unordered_map<Bitvector_t, std::unordered_set<Bitvector_t, Hasher<Bitvector_t>>, Hasher<Bitvector_t>> DPTable_t;


	typedef typename EquivalenceClass_t::Iterator ECItr_t;

public:
	GraphRule(BvSet_t joinEdges) : Rule<PlanNode, Operations_t>()
	{
		_joinEdges = joinEdges;
	};


	BvSet_t partition(Bitvector_t &input)const;

	std::unordered_set<Bitvector_t, Hasher<Bitvector_t>> getConnectedPars(Bitvector_t s, Bitvector_t c, Bitvector_t);




	struct BVSet_t
	{
		Bitvector_t _bitvector;
		BVSet_t *_next;
	};

	BvSet_t getConnectedParts(Bitvector_t S, Bitvector_t C, Bitvector_t T) const
	{
		LOG(INFO) << "getConnectedParts";
		LOG(INFO) << "S:					" << S;
		LOG(INFO) << "C:					" << C;
		LOG(INFO) << "T:					" << T;

		BvSet_t O;
		Bitvector_t D, N, U, L, L_new;
		N = getNeighbors(T, S).without(C);
		if (N.size() <= 1)
		{
			Bitvector_t b = S.without(C);
			O.insert({b});
			O.insert({C});
			LOG(INFO) << "o:		" << b;
			return O;
		}
		std::cout << "N" << N << std::endl;
		for (unsigned int i = 0; i < N.capacity(); ++i)
		{
			L_new.reset();
			if (N.test(i))
			{
				L_new.set(i);



				std::cout << "L_new" << L_new << std::endl;
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
					O.insert( {S.without(C)});
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
							O.insert({L});
							U = U.without(L);
						}

					}
				}

			}


		}


		return O;
	}

	Bitvector_t getNeighbors(Bitvector_t relations, Bitvector_t s) const
	{

		Bitvector_t result;
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
		LOG(INFO) << "getNeighbors( relations: " << relations << ", s: " << s << ") : " << result;
		return result;
	}


	BvSet_t MinCutConservative(Bitvector_t &subSetOfRelations, Bitvector_t &connectedRelations, Bitvector_t &excluded) const
	{

		LOG(INFO) << "MinCutConservative";
		LOG(INFO) << "subSetOfRelations:	" << subSetOfRelations;
		LOG(INFO) << "connectedRelations:	" << connectedRelations;
		LOG(INFO) << "excluded:			" << excluded;

		BvSet_t result;

		if (connectedRelations == subSetOfRelations)
		{
			LOG(WARNING) << "RESULT";
			return result;
		}
		if (connectedRelations.is_not_empty())
		{
			result.insert({connectedRelations, getNeighbors(connectedRelations, subSetOfRelations)});
		}
		Bitvector_t excluded_new = excluded;
		Bitvector_t neighborhood = getNeighbors(connectedRelations, subSetOfRelations);
		neighborhood.intersect_with(subSetOfRelations);
		neighborhood = neighborhood.without(excluded);
		for (unsigned int i = 0; i < neighborhood.capacity(); ++i)
		{
			if (neighborhood.test(i))
			{
				Bitvector_t v;
				v.set(i);
				BvSet_t O = getConnectedParts(subSetOfRelations, connectedRelations.uni(v), v);
				excluded_new.union_with(v);
				for (Bitvector_t o : O)
				{
					Bitvector_t newConnectedRelationships;
					newConnectedRelationships = subSetOfRelations.without(o);
					BvSet_t r = MinCutConservative(subSetOfRelations, newConnectedRelationships, excluded_new);
					result.insert(r.begin(), r.end());
				}
			}
		}
        for(Bitvector_t b : result)
        {
            LOG(WARNING) << "BITVECTOR:     " << b;
        }
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
	bool isApplicable(PlanNode &aPlanNode) const override
	{
		// IF is Parent Node
		return aPlanNode.getOperator() == JOIN;
	};

	Bitvector_t &merge(Bitvector_t bv1, Bitvector_t bv2) const
	{
		LOG(INFO) << "bv1 + bv2: " << bv1 << ":" << bv2;
		Bitvector_t *js = this->o.get_new_BV();  // =  Bitvector_t();
		js->union_of(bv1, bv2);
		return * js;
	}

	EquivalenceClass_t * createTrees(BvSet_t partition, Bitvector_t js) const
	{
		LOG(INFO) << "CREATE TREE";
		LOG(INFO) << "js:				" << js;

		EquivalenceClass_t * eq = new EquivalenceClass_t();
		
		for(Bitvector_t t : partition)
		{
			LOG(INFO) << "t:					" << t;
            
            if(js.contains(t))
            {
                if(t.size() == 1 && js.size() == 1)
                {
                    eq->concat( this->o.scan(t) );
                    return eq;
                }else if(partition.count(js.without(t)) > 0)
                {
                    LOG(INFO) << "JOIN" << t << " : " << js.without(t);
                    EquivalenceClass_t & left = *createTrees(partition, t);
                    EquivalenceClass_t & right = *createTrees(partition, js.without(t));
                    eq->concat( this->o.join(left, right));
                }
            }
            #ifdef TESTING_YES
            else
            {
                if(js.contains(t))
                {
                for(Bitvector_t p : partition)
                {
                    LOG(ERROR) << "PART:                " << p;
                }
                    LOG(ERROR) << "EROOR1:                  " << js.without(t);
                LOG(ERROR) << "ERROR:					" << partition.count(t);
                    
                }
            }
            #endif
            
            
			/*if(js.contains(t))
			{
                LOG(WARNING) << "partition.count(js.without(t))" << js.without(t) << ": " << partition.count(js.without(t));
				if(t.size() == 1)
				{
                    if(js.size() == 1) return this->o.scan(t);
                    else if(partition.count(js.without(t)) > 0)
					eq->concat(this->o.join(*this->o.scan(t), * createTrees(partition, js.without(t))));
                    //eq->explored = true;
                    return eq;
				}
				else
				{
                    EquivalenceClass_t * eqNew = this->o.join(*createTrees(partition, t), * createTrees(partition, js.without(t)));
                    LOG(INFO) << "eqNew" << eqNew->getRelations();
					eq->concat(eqNew);
                    LOG(INFO) << eq->getRelations().log2();
				}
			}*/
		}
		return eq;
	}
	

	/**
	 * @brief apply graph rule
	 */
	PlanNode *apply(PlanNode &aPlanNode) const override
	{
		LOG(INFO) << "aPlanNode:" << aPlanNode.getRelations();

		Bitvector_t &js = merge(aPlanNode.l().getRelations(), aPlanNode.r().getRelations());

		LOG(WARNING) << "JS: " << js;
		BvSet_t partition = this->partition(js);
		EquivalenceClass_t * e = this->createTrees(partition, js);
		return e->getFirst();
	};
private:
	BvSet_t _joinEdges;
};

template <typename PlanNode, typename Operations_t>
typename GraphRule<PlanNode, Operations_t>::BvSet_t GraphRule<PlanNode, Operations_t>::partition(Bitvector_t &input)const
{
	LOG(INFO) << "Entered partition";
	BvSet_t empty;
	empty.insert(Bitvector_t());
	Bitvector_t b;
	return MinCutConservative(input, b, b);
};


#endif
