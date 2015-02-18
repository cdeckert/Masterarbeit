//
//  PlanNode.h
//

#ifndef RuleBasedOptimizer_PlanNode_h
#define RuleBasedOptimizer_PlanNode_h

//typedef Bitvector<unsigned int> Bitvector_t;
template <typename Operator_t, typename Bitvector_t>
struct PlanNode
{
public:
    //PlanNode(Bitvector_t & relation) : _relations(relation){};
    PlanNode(Operator_t & op, Bitvector_t & relation) : _relations(op.getRelations()), _operator(op){
        _next = nullptr;
    };
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
    
    
    
    
    
    
private:
    Bitvector_t & _relations;
    Operator_t & _operator;
    PlanNode * _next;

};




#endif
