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

template <typename EquivalenceClass_t, typename Iterator, typename PlanNode_t, typename Bitvector_t, typename RuleSet_t>
class ExhaustiveTransformation
{
    
    typedef ExhaustiveTransformation self_type;
    
public:
    ExhaustiveTransformation()
    {
        planNodes = new Reservoir<PlanNode_t>(300);
        com = new CommutativityRule<PlanNode_t>(planNodes);
        leftAsso = new LeftAssociativity<PlanNode_t, EquivalenceClass_t>();
    };
    void apply(EquivalenceClass_t * aEquivalenceClass) const
    {
        std::vector<EquivalenceClass_t *> toDo;
        std::vector<EquivalenceClass_t *> done;
        toDo.push_back(aEquivalenceClass);
        
        std::unordered_set<Bitvector_t, Hasher<Bitvector_t>> knownEQSignatures;
        
        
        while(!toDo.empty())
        {
            std::unordered_set<Bitvector_t, Hasher<Bitvector_t>> knownPlans;
            EquivalenceClass_t * eq = toDo.back();
            toDo.pop_back();
            for(Iterator itr = eq->begin(); itr.isOK(); ++ itr)
            {
                
                if(com->isApplicable(*itr.node()))
                {
                    knownPlans.insert(itr.node()->getSignature());
                    PlanNode_t * p = com->apply(itr.node());
                    if(knownPlans.count(p->getSignature()) == 0)
                    {
                        eq->push_back(p);
                        knownPlans.insert(p->getLeft()->getSignature());
                        std::cout << std::endl << std::endl << "EQ";
                        std::cout.flush();
                    }
                }
                
                if(leftAsso->isApplicable(*itr.node()))
                {
                    PlanNode_t * p = leftAsso->apply(itr.node());
                    if(knownPlans.count(p->getLeft()->getSignature()) == 0)
                    {
                        eq->push_back(p);
                        knownPlans.insert(p->getSignature());
                        std::cout << std::endl << std::endl << "EQ";
                        std::cout.flush();
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
                
                done.push_back(eq);
                
                
            }
        }
        
    };

private:
    CommutativityRule<PlanNode_t> * com;
    LeftAssociativity<PlanNode_t, EquivalenceClass_t> * leftAsso;
    Reservoir<PlanNode_t> * planNodes;
};

#endif
