//
//  ExhaustiveTransformation.h
//

#ifndef RuleBasedOptimizer_ExhaustiveTransformation_h
#define RuleBasedOptimizer_ExhaustiveTransformation_h

#include <unordered_set>
#include <iostream>
#include "Hasher.h"
#include "RuleSet.h"


template <typename EquivalenceClass_t, typename Iterator,
typename PlanNode_t, typename Bitvector_t,
typename Operations_t, typename Rule_t>
class ExhaustiveTransformation
{
    typedef RuleSet<Rule_t> RuleSet_t;
    
    typedef ExhaustiveTransformation self_type;
    
public:
    ExhaustiveTransformation(RuleSet_t aRuleSet)
    {
        _rulset = aRuleSet;
    };
    void apply(EquivalenceClass_t & aEquivalenceClass) const
    {
        // toDo List
        std::vector<EquivalenceClass_t *> toDo;
        std::unordered_set<Bitvector_t, Hasher<Bitvector_t>> knownEQSignatures;
        
        // add new equivalence to todo list
        toDo.push_back(& aEquivalenceClass);
        
        while(!toDo.empty())
        {
            std::unordered_set<Bitvector_t, Hasher<Bitvector_t>> knownPlans;
            EquivalenceClass_t * eq = toDo.back();
            toDo.pop_back();
            for(Iterator itr = eq->begin(); itr.isOK(); ++ itr)
            {
                
                for(unsigned int i = 0; i < _rulset._size; ++i)
                {
                    if(_rulset._rules[i]->isApplicable(*itr.node()))
                    {
                        knownPlans.insert(itr->getSignature());
                         PlanNode_t * p = _rulset._rules[i]->apply(*itr.node());
                         if(knownPlans.count(p->getSignature()) == 0)
                         {
                             eq->push_back(*p);
                             knownPlans.insert(p->getLeft().getSignature());
                         }
                    }
                }
                
                
                
                if(itr->hasLeft() && knownEQSignatures.count(itr->getLeft().getSignature()) == 0)
                {
                    toDo.push_back(&itr->getLeft());
                    knownEQSignatures.insert(itr->getLeft().getSignature());
                }
                if(itr->hasRight() && knownEQSignatures.count(itr->getRight().getSignature()) == 0)
                {
                    toDo.push_back(&itr->getRight());
                    knownEQSignatures.insert(itr->getRight().getSignature());
                }
                
                
                
            }
        }
        
    };

private:
    RuleSet_t _rulset;
};

#endif
