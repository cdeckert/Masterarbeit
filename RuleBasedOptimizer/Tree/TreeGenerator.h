//
//  TreeGenerator.h
//

#ifndef __RuleBasedOptimizer__TreeGenerator__
#define __RuleBasedOptimizer__TreeGenerator__

#include <stdio.h>
#include <vector>
#include "EquivalenceClass.h"
#include "BitvectorSmall.h"

typedef BitVectorSmall<int> Bitvector;
// TO-Do: Remove class!!!
// Reservoir Implementierung nicht vergessen!!!
class TreeGenerator {
    
public:
    static EquivalenceClass<Bitvector> * generate();
};




#endif /* defined(__RuleBasedOptimizer__TreeGenerator__) */

