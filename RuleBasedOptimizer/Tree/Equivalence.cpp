//
//  Equivalence.cpp
//

#include "Equivalence.h"

Reservoir<Equivalence> Equivalence::equivalences(10); // = new Reservoir<Equivalence>(300);
//std::unordered_map<std::vector<int>, Equivalence*> Equivalence::knownEquivalences;


/**
 * @brief Based on a relationship vector a corresponding equivalance is returned, in case the equivalance is unknown a new equivalance will be generated using a reservoir
 * @param relationship vector
 * @return corresponding equivalence
 */
Equivalence * Equivalence::get(std::vector<int> relations)
{
    
    
   
    //return newEquivalence;
    
    
    //if(knownEquivalences.count(relations) == 0)
    //{
        Equivalence * newEquivalence = equivalences.get_new_entry();
        return newEquivalence;
        //knownEquivalences.insert({{relations, newEquivalence}});
    //}
    //return knownEquivalences.at(relations);
    return NULL;
}




Equivalence::Equivalence()
{
    
}


bool Equivalence::isTransformationRulesApplied()
{
    return this->transformationRuleApplied;
}

void Equivalence::setTransformationRulesApplied()
{
    this->transformationRuleApplied = true;
}

void Equivalence::addPlan(Plan * plan)
{
    this->plans.push_back(plan);
}


