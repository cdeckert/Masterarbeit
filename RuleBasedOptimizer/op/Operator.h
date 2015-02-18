//
//  Operator.h
//

#ifndef RuleBasedOptimizer_Operator_h
#define RuleBasedOptimizer_Operator_h

#include <string>

template <typename EquivalenceClass, typename Bitvector>
class Operator
{
    
public:
    Operator(std::string name)
    {
        _name = name;
    };
private:
    std::string _name;
    virtual const Bitvector & getRelations();
};

#endif
