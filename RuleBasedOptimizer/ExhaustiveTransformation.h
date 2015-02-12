//
//  ExhaustiveTransformation.h
//

#ifndef __RuleBasedOptimizer__ExhaustiveTransformation__
#define __RuleBasedOptimizer__ExhaustiveTransformation__

#include <stdio.h>
#include <vector>

template <typename EquivalenceClass, typename PlanNode, typename Ruleset>
class ExhaustiveTransformation
{
    std::vector<EquivalenceClass*> toDo;
    std::vector<EquivalenceClass*> done;
    Ruleset * ruleSet;

    
public:
    ExhaustiveTransformation(Ruleset *);
    EquivalenceClass * execute(EquivalenceClass *);
    std::vector<EquivalenceClass*> applyTransormation(EquivalenceClass *);
};





//implementierung

template <typename EquivalenceClass, typename PlanNode, typename Ruleset>
ExhaustiveTransformation<EquivalenceClass, PlanNode, Ruleset>::ExhaustiveTransformation(Ruleset * ruleSet)
{
    this->ruleSet = ruleSet;
}

template <typename EquivalenceClass, typename PlanNode, typename Ruleset>
EquivalenceClass * ExhaustiveTransformation<EquivalenceClass, PlanNode, Ruleset>::execute(EquivalenceClass* equivalence)
{
    toDo.push_back(equivalence);
    while(!toDo.empty())
    {
        EquivalenceClass * e = toDo.back();
        toDo.pop_back();
        done.push_back(e);
        std::vector<EquivalenceClass*> newEquivalences = applyTransormation(e);
        
    }
    
    return NULL;
}


template <typename EquivalenceClass, typename PlanNode, typename Ruleset>
std::vector<EquivalenceClass*> ExhaustiveTransformation<EquivalenceClass, PlanNode, Ruleset>::applyTransormation(EquivalenceClass * equivalence)
{
    std::vector<EquivalenceClass*> newEquivalences;
    for(PlanNode * p : equivalence->getPlans())
    {
        PlanNode * pNew = ruleSet->commutativity(p);
        /*if(equivalence->addNode(pNew))
        {
            std::cout <<
            for(EquivalenceClass* e : pNew->getEquivalences())
            {
                newEquivalences.push_back(e);
            }
        }*/
        
        /*pNew = ruleSet->leftAssociativity(p);
        if(equivalence->addNode(pNew))
        {
            for(EquivalenceClass* e : pNew->getEquivalences())
            {
                newEquivalences.push_back(e);
            }
        }
        
        pNew = ruleSet->rightAssociativity(p);
        if(equivalence->addNode(pNew))
        {
            for(EquivalenceClass* e : pNew->getEquivalences())
            {
                newEquivalences.push_back(e);
            }
        }*/
    }
    return newEquivalences;
}


#endif /* defined(__RuleBasedOptimizer__ExhaustiveTransformation__) */