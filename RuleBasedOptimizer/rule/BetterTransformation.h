//
//  BetterTransformation.h
//

#ifndef RuleBasedOptimizer_BetterTransformation_h
#define RuleBasedOptimizer_BetterTransformation_h

#include <unordered_set>
#include <iostream>
#include "Hasher.h"
#include "RuleSet.h"


template <typename PlanNode_t, typename Operations_t, typename Rule_t>
class BetterTransformation
{
	typedef typename PlanNode_t::EquivalenceClass_t EquivalenceClass_t;
	typedef typename PlanNode_t::BV Bitvector_t;

	typedef std::unordered_map<Bitvector_t, EquivalenceClass_t, Hasher<Bitvector_t>> EquivalenceClassMap_t;
    typedef BitVectorSmall<uint64_t> BitvectorMax_t;
    
    typedef std::unordered_map<Bitvector_t, std::unordered_set<BitvectorMax_t, Hasher<BitvectorMax_t>>, Hasher<Bitvector_t>> MapSetBitVector_t;

    

	typedef typename EquivalenceClass_t::Iterator Iterator;
	typedef RuleSet<Rule_t> RuleSet_t;
	typedef BetterTransformation self_type;

public:
	BetterTransformation(RuleSet_t aRuleSet)
	{
		_ruleset = aRuleSet;
		_knownEquivalenceClasses.clear();
        _foundEquivalenceClasses.clear();
	}
	void apply(EquivalenceClass_t &) const;





private:
	RuleSet_t _ruleset;
	static EquivalenceClassMap_t _knownEquivalenceClasses;
    static MapSetBitVector_t _foundEquivalenceClasses;
    
    BitvectorMax_t concat(Bitvector_t a, Bitvector_t b)
    {
        BitvectorMax_t result;
        result = a;
        result << b;
        return result;
    }
    
    BitvectorMax_t signature(PlanNode_t & aPlanNode) const
    {
        BitvectorMax_t result;
        Bitvector_t & left = aPlanNode.l().getRelations();
        for(unsigned int i = 0; i < left.capacity(); ++i)
        {
            if(left.test(i)) result.set(i);
        }
        if(aPlanNode.hasRight())
        {
            Bitvector_t & right = aPlanNode.r().getRelations();
            for(unsigned int i = 0; i < right.capacity(); ++i)
            {
                unsigned int position = i+left.capacity();
                if(right.test(i)) result.set(position);
            }
        }
        //LOG(INFO) << "Signature"<< result;
        return result;
    }
};

//
// Implementation
//

template <typename PlanNode_t, typename Operations_t, typename Rule_t>
std::unordered_map<typename PlanNode_t::BV, typename PlanNode_t::EquivalenceClass_t, Hasher<typename PlanNode_t::BV>> BetterTransformation<PlanNode_t, Operations_t, Rule_t>::_knownEquivalenceClasses;


template <typename PlanNode_t, typename Operations_t, typename Rule_t>
std::unordered_map<typename PlanNode_t::BV, std::unordered_set<BitVectorSmall<uint64_t>, Hasher<BitVectorSmall<uint64_t>>>, Hasher<typename PlanNode_t::BV>> BetterTransformation<PlanNode_t, Operations_t, Rule_t>::_foundEquivalenceClasses;

template <typename PlanNode_t, typename Operations_t, typename Rule_t>
void BetterTransformation<PlanNode_t, Operations_t, Rule_t>::apply(BetterTransformation<PlanNode_t, Operations_t, Rule_t>::EquivalenceClass_t &aEquivalenceClass) const
{
    //std::cout << aEquivalenceClass.getSignature() << std::endl;
    
    

	//LOG(INFO) << "Start\t"<<  aEquivalenceClass.getRelations();

	typedef typename EquivalenceClass_t::Iterator EItr;
	// insert to known map in case it doesnt exist
	if (_knownEquivalenceClasses.count(aEquivalenceClass.getRelations()) == 0)
	{
		_knownEquivalenceClasses.insert({{aEquivalenceClass.getRelations(), aEquivalenceClass}});
	}
    
    if(_foundEquivalenceClasses.count(aEquivalenceClass.getRelations()) == 0)
    {
        _foundEquivalenceClasses.insert({{aEquivalenceClass.getRelations(), {{}}}});
    }
    if(aEquivalenceClass.getSize() > 0)
    {
        _foundEquivalenceClasses.at(aEquivalenceClass.getRelations()).insert({{signature(* aEquivalenceClass.getFirst())}});
    }
    
    if(aEquivalenceClass.isBaseRelation())
    {
        _knownEquivalenceClasses.insert({{aEquivalenceClass.getRelations(), aEquivalenceClass}});
        //std::cout << "SMALL";
    }
    else
    {
	//LOG(INFO) << "INTER\t"<<  aEquivalenceClass.getRelations();


	
	//LOG(INFO) << "INTER2\t"<<  aEquivalenceClass.getRelations();
	std::unordered_set<Bitvector_t, Hasher<Bitvector_t>> knownEQSignatures;
	bool isNew = true;
    int i = 0;
	while (isNew)
	{
        //apply transformation to children in case they are unexplored
        for (EItr eq = aEquivalenceClass.begin(); eq.isOK(); ++eq)
        {
            apply(eq->l());
            
            //LOG(INFO) << "APPLY TO: " << eq->l().getRelations();
            if (eq->hasRight())
            {
                apply(eq->r());
                //LOG(INFO) << "APPLY TO: " << eq->r().getRelations();
            }
        }
        i++;
        
        //if(i > 1) LOG(INFO) << "RE RUN";
        
        
        //LOG(INFO) << "RUN: "<< i;
		isNew = false;
		for (EItr eq = aEquivalenceClass.begin(); eq.isOK(); ++eq)
		{
            if(!eq->l().isBaseRelation())
            {
            apply(eq->l());
            }
            if (eq->hasRight() && !eq->r().isBaseRelation())
			{
                apply(eq->r());
				knownEQSignatures.insert({{eq.node()->getSignature()}});
				for (EItr leftItr = eq->l().begin(); leftItr.isOK(); ++ leftItr)
				{
                    
					for (EItr rightItr = eq->r().begin(); rightItr.isOK(); ++rightItr)
					{
                        for (Rule_t *r : _ruleset.getRules())
						{
							if (r->isApplicable(* eq.node(), * leftItr.node(), * rightItr.node()))
							{
								PlanNode_t *p = r->apply(* eq.node(), * leftItr.node(), * rightItr.node());
                                
                                
                                
                                

								// if left or right is known
								if (_knownEquivalenceClasses.count(p->l().getRelations()) != 0)
								{
									p->setLeft(& _knownEquivalenceClasses.at(p->l().getRelations()));
								}
                                else if(!p->l().isBaseRelation())
                                {
                                    apply(p->l());
                                }
                                
								if (_knownEquivalenceClasses.count(p->r().getRelations()) != 0)
								{
									p->setRight(& _knownEquivalenceClasses.at(p->r().getRelations()));
								}
                                else if(!p->l().isBaseRelation()){
                                    apply(p->r());
                                }

								//LOG(WARNING) << "SIG\t\t"<< p->getSignature();
                                //LOG(INFO) << r->getName();
                                if(_foundEquivalenceClasses.at(aEquivalenceClass.getRelations()).count(signature(*p)) == 0)
                                {
                                    if(_foundEquivalenceClasses.count(aEquivalenceClass.getRelations()) == 0)
                                    {
                                        //std::cout << "ADD\n";
                                        _foundEquivalenceClasses.insert({{aEquivalenceClass.getRelations(),{{}}}});
                                        //std::cout << _foundEquivalenceClasses.count(aEquivalenceClass.getRelations());
                                    }
                                    aEquivalenceClass.push_back(* p);
                                    knownEQSignatures.insert({{p->getSignature()}});
                                    isNew = true;
                                    //std::cout << _foundEquivalenceClasses.count(aEquivalenceClass.getRelations());
                                    //std::cout << signature(*p);
                                    //std::cout << std::endl;
                                    _foundEquivalenceClasses.at(aEquivalenceClass.getRelations());
                                    _foundEquivalenceClasses.at(aEquivalenceClass.getRelations()).insert({{signature(*p)}});

                                }

							}
						}
					}
				}



			}
        }
        
        
        //LOG(INFO) << "ERUN:" << i;
	}
	//LOG(INFO) << "END\t\t"<<  aEquivalenceClass.getRelations();
    }


};

#endif
