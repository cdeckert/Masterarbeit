//
//  ExhaustiveTransformation.h
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 19/02/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#ifndef RuleBasedOptimizer_ExhaustiveTransformation_h
#define RuleBasedOptimizer_ExhaustiveTransformation_h

#include <unordered_set>
#include "Hasher.h"
#include "BasicRuleSet.h"
#include "Commutativity.h"
#include "LeftAssociativity.h"
#include "RightAssociativity.h"

template <typename EquivalenceClass_t, typename Iterator, typename PlanNode_t, typename Bitvector_t>
class ExhaustiveTransformation
{
    
    typedef ExhaustiveTransformation self_type;
    typedef Rule<PlanNode_t> Rule_t;
    typedef RuleSet<Rule_t> Ruleset_t;
    
public:
    ExhaustiveTransformation()
    {};
    void apply(EquivalenceClass_t & aEquivalenceClass) const
    {
        CommutativityRule<PlanNode_t>  && commutativity = CommutativityRule<PlanNode_t>();
        LeftAssociativity<PlanNode_t, EquivalenceClass_t>  && leftAssociativity = LeftAssociativity<PlanNode_t, EquivalenceClass_t>();
        RightAssociativity<PlanNode_t, EquivalenceClass_t>  && rightAssociativity = RightAssociativity<PlanNode_t, EquivalenceClass_t>();
        std::vector<EquivalenceClass_t *> eqs;
        eqs.push_back(&aEquivalenceClass);
        while(!eqs.empty())
        {
            EquivalenceClass_t * equivalenceClass = eqs.back();
            eqs.pop_back();
            std::unordered_set<Bitvector_t, Hasher<Bitvector_t>> knownBitvectors;
        
            knownBitvectors.insert(equivalenceClass->begin()._node->getLeft());
        
            for(Iterator itr = equivalenceClass->begin(); itr != equivalenceClass->end() && itr._node != NULL; ++itr)
            {
                
                if(itr._node != NULL)
                {
                    PlanNode_t * comPlan = commutativity.apply(*itr._node);
                    if(knownBitvectors.count(comPlan->getLeft()) == 0)
                    {
                        equivalenceClass->push_back(*comPlan);
                    }
                    
                    if(leftAssociativity.isApplicable(*itr._node))
                    {
                        PlanNode_t * leftAssoc = leftAssociativity.apply(*itr._node);
                        if(knownBitvectors.count(leftAssoc->getLeft()) == 0)
                        {
                            equivalenceClass->push_back(*leftAssoc);
                        }
                    }
                    
                    if(rightAssociativity.isApplicable(*itr._node))
                    {
                        PlanNode_t * rightAssoc = rightAssociativity.apply(*itr._node);
                        if(knownBitvectors.count(rightAssoc->getLeft()) == 0)
                        {
                            equivalenceClass->push_back(*rightAssoc);
                        }
                    }
            
            
                }
            
            
            //std::cout << itr->getRelations() << std::endl;
                for(EquivalenceClass_t * eq : equivalenceClass->getChildECs())
                {
                    if(knownBitvectors.count(eq->begin()._node->getLeft()) == 0)
                    {
                        knownBitvectors.insert(eq->begin()._node->getLeft());
                        eqs.push_back(eq);
                    }
                    
                }
                
            }
        }
    };

private:
};

#endif
