//
//  EquivalenceClass.h
//
//

#ifndef __RuleBasedOptimizer__EquivalenceClass__
#define __RuleBasedOptimizer__EquivalenceClass__

#include <stdio.h>
#include <unordered_set>
#include "PlanNode.h"
#include <string>
#include <iostream>
#include <sstream>




template <typename Bitvector>
struct EquivalenceClass
{
    void init();
    Bitvector relationships; 
    std::unordered_set<Bitvector, Hasher<Bitvector>> planSignatures;
    std::unordered_set<PlanNode<Bitvector> *> plans;
    
public:
    EquivalenceClass();
    EquivalenceClass(int);
    EquivalenceClass(Bitvector);
    EquivalenceClass(PlanNode<Bitvector>*);
    void setRelationships(Bitvector);
    Bitvector getRelationships();
    bool addNode(PlanNode<Bitvector>*);
    
    std::string toString();
    
    std::unordered_set<PlanNode<Bitvector>*> getPlans();
    
};


template <typename Bitvector>
void EquivalenceClass<Bitvector>::init()
{
    this->relationships = Bitvector();
    //this->plans = nullptr;
}





// Implementation



template <typename Bitvector>
EquivalenceClass<Bitvector>::EquivalenceClass()
{
    this->init();
}

template <typename Bitvector>
EquivalenceClass<Bitvector>::EquivalenceClass(int nodeName)
{
    this->init();
    this->setRelationships(Bitvector(nodeName));
}

template <typename Bitvector>
EquivalenceClass<Bitvector>::EquivalenceClass(Bitvector relationships)
{
    this->init();
    this->setRelationships(relationships);
}


template <typename Bitvector>
EquivalenceClass<Bitvector>::EquivalenceClass(PlanNode<Bitvector> * planNode)
{
    this->init();
    this->addNode(planNode);
}

template <typename Bitvector>
void EquivalenceClass<Bitvector>::setRelationships(Bitvector relationships)
{
    this->relationships = relationships;
}

template <typename Bitvector>
std::unordered_set<PlanNode<Bitvector>*> EquivalenceClass<Bitvector>::getPlans()
{
    return plans;
}

/**
 * @brief converts DAG to String
 */

//To to: schlimm.. ostringstream
template <typename Bitvector>
std::string EquivalenceClass<Bitvector>::toString()
{
    std::ostringstream stream;
    std::string result = "EquivalenceClass:{";
    
    this->relationships.print(stream);
    result += stream.str();
    
    for(PlanNode<Bitvector> * pn : this->plans)
    {
        result += pn->toString()+",";
    }
    result += "}\n";
    return result;
}


/**
 * @brief returns relationships
 */
template <typename Bitvector>
Bitvector EquivalenceClass<Bitvector>::getRelationships()
{
    return this->relationships; // something is going wrong....
}

/**
 * @brief checks if plan is known and adds new plans to the equivalence
 */
template <typename Bitvector>
bool EquivalenceClass<Bitvector>::addNode(PlanNode<Bitvector> * planNode)
{
    if(this->planSignatures.empty())
    {
        this->planSignatures.insert(planNode->getRelationships());
        this->plans.insert(planNode);
        this->relationships += planNode->getRelationships();
        return false;
    }
    return true;
    
}

#endif /* defined(__RuleBasedOptimizer__EquivalenceClass__) */
