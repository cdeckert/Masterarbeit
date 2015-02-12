//
//  Rule.h
//

#ifndef RuleBasedOptimizer_Rule_h
#define RuleBasedOptimizer_Rule_h

template <typename PlanNode>
class Rule
{
public:
    Rule();
    virtual PlanNode & apply(PlanNode& const) = 0;
};
#endif
