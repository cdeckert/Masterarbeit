//
//  LeftAssociativity.h
//

#ifndef RuleBasedOptimizer_LeftAssociativity_h
#define RuleBasedOptimizer_LeftAssociativity_h


template <typename PlanNode, typename Operations_t>
class LeftAssociativity : public Rule<PlanNode, Operations_t>
{
    typedef Rule<PlanNode, Operations_t> Rule_t;
    
public:
    
    PlanNode * apply(PlanNode * aPlanNode) const override
    {
    return Rule_t::o->joinPN(aPlanNode->getLeft()->begin().node()->getLeft(), Rule_t::o->join(aPlanNode->getLeft()->begin().node()->getRight(), aPlanNode->getRight()));
        //return Rule_t::o->joinPN(
        //                         aPlanNode->getLeft()->begin().node()->getLeft(),
        //                         Rule_t::o->join(aPlanNode->getLeft()->begin().node()->getRight(), aPlanNode->getRight())
              //                   );
    
    
    };
    bool isApplicable(PlanNode & aPlanNode) const override
    {
        return aPlanNode.getOperator() == JOIN && aPlanNode.getLeft()->begin().node()->getOperator() == JOIN;
    };
};


#endif
