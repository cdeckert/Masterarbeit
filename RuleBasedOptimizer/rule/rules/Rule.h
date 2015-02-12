//
//  Rule.h
//

#ifndef RuleBasedOptimizer_Rule_h
#define RuleBasedOptimizer_Rule_h

template <typename Equivalence>
class Rule
{
public:
    Rule();
    virtual bool apply(Equivalence&);
};
#endif
