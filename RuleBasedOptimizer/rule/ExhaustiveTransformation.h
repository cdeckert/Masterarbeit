//
//  ExhaustiveTransformation.h
//

#ifndef RuleBasedOptimizer_ExhaustiveTransformation_h
#define RuleBasedOptimizer_ExhaustiveTransformation_h

#include <unordered_set>
#include <iostream>
#include "Commutativity.h"
#include "Hasher.h"
#include "Reservoir.h"
#include "LeftAssociativity.h"

template <typename EquivalenceClass_t, typename Iterator,
typename PlanNode_t, typename Bitvector_t,
typename RuleSet_t, typename Operations_t>
class ExhaustiveTransformation
{
    
    typedef ExhaustiveTransformation self_type;
    
public:
    ExhaustiveTransformation()
    {
        com = CommutativityRule<PlanNode_t, Operations_t>();
        leftAsso = LeftAssociativity<PlanNode_t, Operations_t>();
    };
    void apply(EquivalenceClass_t * aEquivalenceClass) const
    {
        // toDo List
        std::vector<EquivalenceClass_t *> toDo;
        std::unordered_set<Bitvector_t, Hasher<Bitvector_t>> knownEQSignatures;
        
        // add new equivalence to todo list
        toDo.push_back(aEquivalenceClass);
        std::unordered_set<Bitvector_t, Hasher<Bitvector_t>> knownPlans;
        while(!toDo.empty())
        {
            
            EquivalenceClass_t * eq = toDo.back();
            toDo.pop_back();
            for(Iterator itr = eq->begin(); itr.isOK(); ++ itr)
            {
                
                if(com.isApplicable(*itr.node()))
                {
                    knownPlans.insert(itr.node()->getSignature());
                    PlanNode_t * p = com.apply(itr.node());
                    if(knownPlans.count(p->getSignature()) == 0)
                    {
                        eq->push_back(p);
                        knownPlans.insert(p->getLeft()->getSignature());
                    }
                }
                
                if(leftAsso.isApplicable(*itr.node()))
                {
                    PlanNode_t * p = leftAsso.apply(itr.node());
                    if(knownPlans.count(p->getLeft()->getSignature()) == 0)
                    {
                        eq->push_back(p);
                        knownPlans.insert(p->getSignature());
                    }
                }

                
                
                
                if(itr.node()->hasLeft() && knownEQSignatures.count(itr.node()->getLeft()->getSignature()) == 0)
                {
                    toDo.push_back(itr.node()->getLeft());
                    knownEQSignatures.insert(itr.node()->getLeft()->getSignature());
                }
                if(itr.node()->hasRight() && knownEQSignatures.count(itr.node()->getRight()->getSignature()) == 0)
                {
                    toDo.push_back(itr.node()->getRight());
                    knownEQSignatures.insert(itr.node()->getRight()->getSignature());
                }
                
                
                
            }
        }
        
    };

private:
    CommutativityRule<PlanNode_t, Operations_t> com;
    LeftAssociativity<PlanNode_t, Operations_t> leftAsso;
};

#endif
