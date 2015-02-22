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
    typedef Descendant<Bitvector_t, EquivalenceClass_t> Descendant_t;
    
public:
    ExhaustiveTransformation()
    {};
    void apply(EquivalenceClass_t & aEquivalenceClass) const
    {
        CommutativityRule<PlanNode_t>  && commutativity = CommutativityRule<PlanNode_t>();
        LeftAssociativity<PlanNode_t, EquivalenceClass_t, Descendant_t>  && leftAssociativity = LeftAssociativity<PlanNode_t, EquivalenceClass_t, Descendant_t>();
        //RightAssociativity<PlanNode_t, EquivalenceClass_t>  && rightAssociativity = RightAssociativity<PlanNode_t, EquivalenceClass_t>();
        std::vector<EquivalenceClass_t *> eqs;
        eqs.push_back(&aEquivalenceClass);
        std::unordered_set<Bitvector_t, Hasher<Bitvector_t>> knownBitvectors;
        while(!eqs.empty())
        {
            EquivalenceClass_t * equivalenceClass = eqs.back();
            eqs.pop_back();
            
        
            knownBitvectors.insert(equivalenceClass->begin()._node->getSignature());
        
            for(Iterator itr = equivalenceClass->begin(); itr.isNext(); ++itr)
            {
                
                    PlanNode_t * comPlan = commutativity.apply(*itr._node);
                    if(knownBitvectors.count(comPlan->getSignature()) == 0)
                    {
                        equivalenceClass->push_back(*comPlan);
                        
                        
                    }
                    
                    if(leftAssociativity.isApplicable(*itr._node))
                    {
                        std::cout << std::endl << "itr._node->str(): "<< itr._node->str() << " " << std::endl;
                        
                        
                        
                        
                        std::cout << "BEFORE: " << itr._node;
                        
                        std::cout << "itr._node->_leftDecendent._ec->_begin->_leftDecendent._relations:\n"<< itr._node->_leftDecendent._ec->_begin->_leftDecendent._relations << "\n\n";
                        std::cout.flush();
                        
                        
                        
                        PlanNode_t * leftAssoc = leftAssociativity.apply(*itr._node);
                        if(knownBitvectors.count(leftAssoc->getSignature()) == 0)
                        {
                            
                            equivalenceClass->push_back(*leftAssoc);
                            std::cout  << "NEU NEU NEU" << leftAssoc->str() << std::endl;
                        }
                        std::cout << leftAssoc->getSignature() << " ";
                        
                        std::cout << "itr._node->_leftDecendent._ec->_begin->_leftDecendent._relations:\n"<< itr._node->_leftDecendent._ec->_begin->_leftDecendent._relations << "\n\n";
                        std::cout.flush();

                    }
                    
                    /*if(rightAssociativity.isApplicable(*itr._node))
                    {
                        PlanNode_t * rightAssoc = rightAssociativity.apply(*itr._node);
                        if(knownBitvectors.count(rightAssoc->getSignature()) == 0)
                        {
                            equivalenceClass->push_back(*rightAssoc);
                        }
                    }*/
            
                
                    
            
            
            
            
            //std::cout << itr->getRelations() << std::endl;
                /*for(EquivalenceClass_t * eq : equivalenceClass->getChildECs())
                {
                    if(eq != NULL && knownBitvectors.count(eq->getRelations()) == 0)
                    {
                        knownBitvectors.insert(eq->getRelations());
                        
                        std::cout << "NEW" << eq->getRelations() << std::endl;
                        std::cout.flush();
                        eqs.push_back(eq);
                    }
                    
                }*/
                
            }
        }
    };

private:
};

#endif
