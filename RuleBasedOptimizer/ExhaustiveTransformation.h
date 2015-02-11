//
//  ExhaustiveTransformation.h
//

#ifndef __RuleBasedOptimizer__ExhaustiveTransformation__
#define __RuleBasedOptimizer__ExhaustiveTransformation__

#include <stdio.h>
#include <vector>


template <typename EquivalenceClass, typename PlanNode>
class ExhaustiveTransformation {
    std::vector<EquivalenceClass*> toDo;
    std::vector<EquivalenceClass*> done;

    
public:
    PlanNode * execute(EquivalenceClass *);
    std::vector<EquivalenceClass> applyTransormation(EquivalenceClass *);
};


#endif /* defined(__RuleBasedOptimizer__ExhaustiveTransformation__) */