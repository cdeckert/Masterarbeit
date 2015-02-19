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

template <typename EquivalenceClass_t, typename Iterator, typename PlanNode_t, typename Bitvector_t>
class ExhaustiveTransformation {
    
    typedef ExhaustiveTransformation self_type;
    typedef Rule<PlanNode_t> Rule_t;
    typedef BasicRuleSet<Rule_t> Ruleset_t;
    
public:
    ExhaustiveTransformation(Ruleset const & ruleset): _ruleset(ruleset){};
    void apply(EquivalenceClass_t & equivalenceClass)
    {
        std::unordered_set<Bitvector_t, Hasher<Bitvector_t>> knownBitvectors;
        
        knownBitvectors.insert(equivalenceClass.begin()->getRelations());
        for(Iterator itr = equivalenceClass.begin(); itr != equivalenceClass.end(); ++itr)
        {
            for(Rule_t r : _ruleset.rules)
            {
                PlanNode_t & planNode = r.apply(&itr);
            }
            std::cout << itr->getRelations() << std::endl;
        }
    };

private:
    Ruleset_t & _ruleset;
};

#endif
