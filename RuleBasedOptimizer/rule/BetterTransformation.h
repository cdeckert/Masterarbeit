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
    struct ToDo
    {
        EquivalenceClass_t & _eq;
        PlanNode_t & _parent;
        PlanNode_t & _left;
        PlanNode_t & _right;
        
        ToDo(EquivalenceClass_t eq, PlanNode_t & parent, PlanNode_t & left, PlanNode_t & right): _eq(eq), _parent(parent), _left(left), _right(right){};
    };
    
    
    typedef typename EquivalenceClass_t::Iterator Iterator;
    typedef RuleSet<Rule_t> RuleSet_t;
    typedef BetterTransformation self_type;
    typedef std::vector<ToDo> ToDoList;
    
public:
    BetterTransformation(RuleSet_t aRuleSet)
    {
        _ruleset = aRuleSet;
    }
    void apply(EquivalenceClass_t &) const;
    
    
    
    
    
private:
    RuleSet_t _ruleset;
    static EquivalenceClassMap_t knownEquivalenceClasses;
};

//
// Implementation
//

template <typename PlanNode_t, typename Operations_t, typename Rule_t>
std::unordered_map<typename PlanNode_t::BV, typename PlanNode_t::EquivalenceClass_t, Hasher<typename PlanNode_t::BV>> BetterTransformation<PlanNode_t, Operations_t, Rule_t>::knownEquivalenceClasses;

template <typename PlanNode_t, typename Operations_t, typename Rule_t>
void BetterTransformation<PlanNode_t, Operations_t, Rule_t>::apply(BetterTransformation<PlanNode_t, Operations_t, Rule_t>::EquivalenceClass_t &aEquivalenceClass) const
{
    
    
    LOG(INFO) << aEquivalenceClass.getSignature();
    
    typedef typename EquivalenceClass_t::Iterator EItr;
    // insert to known map in case it doesnt exist
    if(knownEquivalenceClasses.count(aEquivalenceClass.getRelations()) == 0)
    {
        knownEquivalenceClasses.insert({{aEquivalenceClass.getRelations(), aEquivalenceClass}});
    }
    
    //apply transformation to children in case they are unexplored
    for(EItr eq = aEquivalenceClass.begin(); eq.isOK(); ++eq)
    {
        if(!eq->l().isExplored()) apply(eq->l());
        if(eq->hasRight() && !eq->r().isExplored()) apply(eq->r());
    }
    std::unordered_set<Bitvector_t, Hasher<Bitvector_t>> knownEQSignatures;
    for(EItr eq = aEquivalenceClass.begin(); eq.isOK(); ++eq)
    {
        if(eq->hasRight())
        {
            knownEQSignatures.insert({{eq.node()->getSignature()}});
            for(EItr leftItr = eq->l().begin(); leftItr.isOK(); ++ leftItr)
            {
                for(EItr rightItr = eq->r().begin(); rightItr.isOK(); ++rightItr)
                {
                    
                    for (Rule_t *r : _ruleset.getRules())
                    {
                        if(r->isApplicable(* eq.node(), * leftItr.node(), * rightItr.node()))
                        {
                            PlanNode_t *p = r->apply(* eq.node(), * leftItr.node(), * rightItr.node());
                            
                            // if left or right is known
                            if(knownEquivalenceClasses.count(p->l().getRelations()) == 0)
                            {
                                apply(p->l());
                                knownEquivalenceClasses.insert({{p->l().getRelations(), p->l()}});
                            }
                            else
                            {
                                p->setLeft(& knownEquivalenceClasses.at(p->l().getRelations()));
                            }
                            
                            if(knownEquivalenceClasses.count(p->r().getRelations()) == 0)
                            {
                                apply(p->r());
                                knownEquivalenceClasses.insert({{p->r().getRelations(), p->r()}});
                            }
                            else
                            {
                                p->setRight(& knownEquivalenceClasses.at(p->r().getRelations()));
                            }
                            if(knownEQSignatures.count(p->getSignature()) == 0)
                            {
                                aEquivalenceClass.push_back(* p);
                                knownEQSignatures.insert({{p->getSignature()}});
                            }
                            
                            
                        }
                    }
                }
            }
            
                
            
        }
    }
    
    
    
};

#endif
