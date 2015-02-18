//
//  PlanNode.h
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 2/16/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#ifndef RuleBasedOptimizer_PlanNode_h
#define RuleBasedOptimizer_PlanNode_h

#include "Bitvector.h"

//typedef Bitvector<unsigned int> Bitvector_t;
template <typename Operator_t, typename Bitvector_t>
struct PlanNode
{
public:
    PlanNode();
    //PlanNode(Bitvector_t & relation) : _relations(relation){};
    PlanNode(Operator_t & op, Bitvector_t & relation) : _relations(relation), _operator(op){};
    PlanNode(const PlanNode &);
    ~PlanNode(){};

    
    
    
    inline const Bitvector_t & getRelations(){ return _relations; };
    const int getPlanNumber() const;
    
    void print()
    {
        std::cout << "print" << std::endl << "RELS";
        getRelations().print();
        std::cout << std::endl;
    }
    void setNext(PlanNode & aPlanNode)
    {
        _next = &aPlanNode;
    }
    PlanNode * getNext()
    {
        return _next;
    }
    
    //PlanNode & operator= (const PlanNode & pn)
    //{ return pn; };
    
    
    
    
    
private:
    Bitvector_t & _relations;
    Operator_t & _operator;
    PlanNode * _next;

};




#endif
