//
//  PlanNode.h
//
//

#ifndef __RuleBasedOptimizer__PlanNode__
#define __RuleBasedOptimizer__PlanNode__

#include <stdio.h>
#include "Hasher.h"


enum Operator {JOIN};

template <typename Bitvector>
struct EquivalenceClass;


template <typename Bitvector>
struct PlanNode
{
    Bitvector relationships;
    Bitvector relationshipsLeft;
    Bitvector relationshipsRight;
    Operator rootOperator;
    EquivalenceClass<Bitvector> * leftEquivalence;
    EquivalenceClass<Bitvector> * rightEquivalence;
    
    void addLeft(int);
    void addLeft(Bitvector);
    void addLeft(EquivalenceClass<Bitvector> *);
    
    void addRight(int);
    void addRight(Bitvector);
    void addRight(EquivalenceClass<Bitvector> *);
    
    void init();
    
public:
    PlanNode(Bitvector);
    PlanNode(Operator, int, int);
    PlanNode(Operator, EquivalenceClass<Bitvector> *, int);
    PlanNode(Operator, int, EquivalenceClass<Bitvector> *);
    PlanNode(Operator, EquivalenceClass<Bitvector> *, EquivalenceClass<Bitvector> *);
    PlanNode(Operator, Bitvector, Bitvector);
    Bitvector getRelationships();
    Operator getOperator();
    
    std::vector<EquivalenceClass<Bitvector>*> getEquivalences();
};





// Implementation





template <typename Bitvector>
PlanNode<Bitvector>::PlanNode(Bitvector relationships)
{
    this->init();
    this->relationships = relationships;
}

/**
 * @brief convenience constructor to create simple nodes
 */
template <typename Bitvector>
PlanNode<Bitvector>::PlanNode(Operator rootOperator, EquivalenceClass<Bitvector> * left, EquivalenceClass<Bitvector> * right)
{
    this->init();
    Bitvector leftVector(left);
    Bitvector rightVector(right);
    
    this->relationships += leftVector;
    this->relationships += rightVector;
    this->relationshipsLeft += leftVector;
    this->relationshipsRight += rightVector;
}



template <typename Bitvector>
Operator PlanNode<Bitvector>::getOperator()
{
    return this->rootOperator;
}





template <typename Bitvector>
void PlanNode<Bitvector>::addLeft(int left)
{
    EquivalenceClass<Bitvector> * leftEquivalence = new EquivalenceClass<Bitvector>::EquivalenceClass(left);
    this->addLeft(leftEquivalence);
}

template <typename Bitvector>
void PlanNode<Bitvector>::addLeft(Bitvector leftVector)
{
    this->relationships += leftVector;
    this->relationshipsLeft += leftVector;
}

template <typename Bitvector>
void PlanNode<Bitvector>::addLeft(EquivalenceClass<Bitvector> * euqivalence)
{
    this->leftEquivalence = euqivalence;
    this->addLeft(euqivalence->getRelationships());
}



template <typename Bitvector>
void PlanNode<Bitvector>::addRight(int right)
{
    Bitvector rightVector(right);
    this->addRight(rightVector);
}

template <typename Bitvector>
void PlanNode<Bitvector>::addRight(Bitvector rightVector)
{
    this->relationships += rightVector;
    this->relationshipsRight += rightVector;
}

template <typename Bitvector>
void PlanNode<Bitvector>::addRight(EquivalenceClass<Bitvector> * euqivalence)
{
    this->rightEquivalence = euqivalence;
    this->addRight(euqivalence->getRelationships());
}








template <typename Bitvector>
PlanNode<Bitvector>::PlanNode(Operator rootOperator, int left, int right)
{
    this->init();
    this->addLeft(left);
    this->addRight(right);
}

template <typename Bitvector>
PlanNode<Bitvector>::PlanNode(Operator rootOperator,EquivalenceClass<Bitvector> * left, int right)
{
    this->init();
    this->addLeft(left);
    this->addRight(right);
}

template <typename Bitvector>
PlanNode<Bitvector>::PlanNode(Operator rootOperator, Bitvector  left, Bitvector  right)
{
    this->init();
    this->addLeft(left);
    this->addRight(right);
}

template <typename Bitvector>
void PlanNode<Bitvector>::init()
{
    //this->leftEquivalence = NULL;
    //this->rightEquivalence = NULL;
    //this->relationshipsLeft = NULL;
    //this->relationshipsRight = NULL;
    //rootOperator = NULL;
}

template <typename Bitvector>
std::vector<EquivalenceClass<Bitvector>*> PlanNode<Bitvector>::getEquivalences()
{
    return std::vector<EquivalenceClass<Bitvector>*>{leftEquivalence, rightEquivalence};
}

template <typename Bitvector>
Bitvector PlanNode<Bitvector>::getRelationships()
{
    return this->relationshipsRight;
}




#endif /* defined(__RuleBasedOptimizer__PlanNode__) */

