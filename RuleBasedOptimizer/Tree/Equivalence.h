//
//  Equivalence.h
//

#ifndef __RuleBasedOptimizer__Equivalence__
#define __RuleBasedOptimizer__Equivalence__

#include <stdio.h>
#include <unordered_map>
#include <vector>

#include "Plan.h"
#include "Reservoir.h"





class Equivalence {
    static Reservoir<Equivalence> equivalences;
    static std::unordered_map<std::vector<int>, Equivalence*> knownEquivalences;
    
    
    
    std::vector<Plan *> plans;
    int identifier;
    bool transformationRuleApplied = false;
    std::vector<int> relations;
    
    
public:
    Equivalence();
    static Equivalence* get(std::vector<int>);
    
    
    
    bool isTransformationRulesApplied();

    
    void addPlan(Plan*);
    void setTransformationRulesApplied();
    void addParent(Plan parent);
    void addParent(Plan parent, bool skip);
    void printDAG();
    
    
};



#endif /* defined(__RuleBasedOptimizer__Equivalence__) */
