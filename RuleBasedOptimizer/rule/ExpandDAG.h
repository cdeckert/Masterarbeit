//
//  ExpandDAG.h
//

#ifndef RuleBasedOptimizer_ExpandDAG_h
#define RuleBasedOptimizer_ExpandDAG_h

#include <unordered_set>
#include <iostream>
#include "Hasher.h"
#include "RuleSet.h"


template <typename PlanNode_t, typename Operations_t, typename Rule_t>
class ExpandDAG
{
    typedef typename PlanNode_t::EquivalenceClass_t EquivalenceClass_t;
    typedef typename PlanNode_t::BV Bitvector_t;
    typedef typename EquivalenceClass_t::Iterator EItr;
    typedef RuleSet<Rule_t> RuleSet_t;
    typedef ExpandDAG self_type;
    
    
    
public:
    ExpandDAG(RuleSet_t ruleSet)
    {
        _ruleset = ruleSet;
        knownVectors.clear();
        knownEqs.clear();
        numberOfPNs = 0;
    };
    
    void apply(EquivalenceClass_t &);
    int numberOfPNs;

private:
    RuleSet_t _ruleset;
    
    static std::unordered_map<Bitvector_t, std::unordered_map<Bitvector_t, PlanNode_t *, Hasher<Bitvector_t>>, Hasher<Bitvector_t>> knownVectors;
    
    static std::unordered_map<Bitvector_t, EquivalenceClass_t &, Hasher<Bitvector_t>> knownEqs;

};

//
// Implementation
//

template <typename PlanNode_t, typename Operations_t, typename Rule_t>
std::unordered_map<typename PlanNode_t::BV, std::unordered_map<typename PlanNode_t::BV, PlanNode_t *, Hasher<typename PlanNode_t::BV>>, Hasher<typename PlanNode_t::BV>> ExpandDAG<PlanNode_t, Operations_t, Rule_t>::knownVectors;

template <typename PlanNode_t, typename Operations_t, typename Rule_t>
std::unordered_map<typename PlanNode_t::BV, typename PlanNode_t::EquivalenceClass_t &, Hasher<typename PlanNode_t::BV>> ExpandDAG<PlanNode_t, Operations_t, Rule_t>::knownEqs;

template <typename PlanNode_t, typename Operations_t, typename Rule_t>
void ExpandDAG<PlanNode_t, Operations_t, Rule_t>::apply(ExpandDAG<PlanNode_t, Operations_t, Rule_t>::EquivalenceClass_t &aEquivalenceClass)
{
    
    for (EItr eq = aEquivalenceClass.begin(); eq.isOK(); ++eq)
    {
        
        //PlanNode_t * eq = opItr.node();
        if(eq->getOperator() == JOIN)
        {
            if(knownVectors.count(eq->r().getRelations()) == 0)
            {
                knownVectors.insert({{eq->r().getRelations(), {{}}}});
                if(knownVectors.at(eq->r().getRelations()).count(eq->l().getRelations()) == 0)
                {
                    knownVectors.at(eq->r().getRelations()).insert({{eq->l().getRelations(), eq.node()}});
                }
            }

            
            
        if(!eq->_explored)
        {
            apply(eq->l());
            if(eq->hasRight())
            {
                apply(eq->r());
            }
           
        }
        
        
        for(EItr lOpItr = eq->l().begin(); lOpItr.isOK(); ++lOpItr)
        {
            if(knownEqs.count(eq->l().getRelations()) == 0) knownEqs.insert({{eq->l().getRelations(), eq->l()}});
            if(knownEqs.count(eq->r().getRelations()) == 0) knownEqs.insert({{eq->r().getRelations(), eq->r()}});
            for(EItr rOpItr = eq->r().begin();rOpItr.isOK(); ++rOpItr)
            {
                for(Rule_t *r : _ruleset.getRules())
                {
                    if(r->isApplicable(*eq.node(), *lOpItr.node(), *rOpItr.node()))
                    {
                        PlanNode_t * pn_new = r->apply(*eq.node(), *lOpItr.node(), *rOpItr.node());
                        
                        if(knownVectors.count(pn_new->r().getRelations()) == 0)
                        {
                            knownVectors.insert({{pn_new->r().getRelations(), {{}}}});
                            
                        }
                        if(knownVectors.at(pn_new->r().getRelations()).count(pn_new->l().getRelations()) == 0)
                        {
                            ++numberOfPNs;
                            knownVectors.at(pn_new->r().getRelations()).insert({{pn_new->l().getRelations(), pn_new}});
                            //pn_new->print();
                            if(knownEqs.count(pn_new->l().getRelations()) == 0)
                            {
                                knownEqs.insert({{pn_new->l().getRelations(), pn_new->l()}});
                            }
                            else
                            {
                                pn_new->setLeft(& knownEqs.at(pn_new->l().getRelations()));
                            }
                            if(knownEqs.count(pn_new->r().getRelations()) == 0)
                            {
                                knownEqs.insert({{pn_new->r().getRelations(), pn_new->r()}});
                            }
                            else
                            {
                                pn_new->setRight(& knownEqs.at(pn_new->r().getRelations()));
                            }
                            aEquivalenceClass.push_back(* pn_new);
                        }
                        
                    }
                }
                
            }
        }
             eq->_explored = true;
        }
        
        
    }
};


#endif
