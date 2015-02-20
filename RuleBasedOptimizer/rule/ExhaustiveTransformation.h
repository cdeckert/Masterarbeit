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

template <typename EquivalenceClass_t, typename Iterator, typename PlanNode_t, typename Bitvector_t>
class ExhaustiveTransformation
{
    
    typedef ExhaustiveTransformation self_type;
    typedef Rule<PlanNode_t> Rule_t;
    typedef RuleSet<Rule_t> Ruleset_t;
    
public:
    ExhaustiveTransformation()
    {};
    void apply(EquivalenceClass_t & equivalenceClass) const
    {
        CommutativityRule<PlanNode_t>  && commutativity = CommutativityRule<PlanNode_t>();
        std::unordered_set<Bitvector_t, Hasher<Bitvector_t>> knownBitvectors;
        
        knownBitvectors.insert(equivalenceClass.begin()._node->getLeft());
        
        for(Iterator itr = equivalenceClass.begin(); itr != equivalenceClass.end() && itr._node != NULL; ++itr)
        {
            if(itr._node != NULL)
            {
                PlanNode_t * comPlan = commutativity.apply(*itr._node);
                if(knownBitvectors.count(comPlan->getLeft()) == 0)
                {
                    equivalenceClass.push_back(*comPlan);
                }
            
            
            /*PlanNode_t && leftAPlan = leftAssociativity.apply(*itr._node);
            if(knownBitvectors.count((leftAPlan).getLeft()) == 0)
            {
                equivalenceClass.push_back(leftAPlan);
            }*/
            }
            
            
            //std::cout << itr->getRelations() << std::endl;
        }
    };

private:
    
    LeftAssociativity<PlanNode_t> leftAssociativity;
};

#endif
