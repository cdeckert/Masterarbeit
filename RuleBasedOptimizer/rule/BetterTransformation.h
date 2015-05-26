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
};

//
// Implementation
//

template <typename PlanNode_t, typename Operations_t, typename Rule_t>
void BetterTransformation<PlanNode_t, Operations_t, Rule_t>::apply(BetterTransformation<PlanNode_t, Operations_t, Rule_t>::EquivalenceClass_t &aEquivalenceClass) const
{
    EquivalenceClassMap_t existingEquivalenceClasses;
    ToDoList toDoList;
    if(aEquivalenceClass.getOperator() == JOIN)
    {
        toDoList.push_back({ToDo(aEquivalenceClass, *aEquivalenceClass.getFirst(), *aEquivalenceClass.getFirst()->l().getFirst(), *aEquivalenceClass.getFirst()->r().getFirst())});
    }
    // collect to dos
    for(ToDo & aToDo : toDoList)
    {
        
    }
    
};

#endif
