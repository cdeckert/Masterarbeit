//
//  Types.h
//

#ifndef RuleBasedOptimizer_Types_h
#define RuleBasedOptimizer_Types_h

#include<stdint.h>

#include "PlanNode.h"
#include "BitvectorSmall.h"
#include "EquivalenceClass.h"
#include "ExhaustiveTransformation.h"
#include "BetterTransformation.h"
#include "RuleSet.h"
#include "RS_B0.h"
#include "RS_B1.h"
#include "RS_B2.h"
#include "Operations.h"


typedef unsigned int u_int;
typedef BitVectorSmall<u_int> Bitvector_t;
typedef PlanNode<Bitvector_t> PlanNode_t;
typedef EquivalenceClass<PlanNode_t> EquivalenceClass_t;
typedef typename EquivalenceClass_t::Iterator EquivalenceClassIterator_t;
typedef Operations<PlanNode_t, u_int> Operations_t;
typedef Rule<PlanNode_t, Operations_t> Rule_t;
typedef RS_B0<PlanNode_t, Operations_t> RS_B0_t;
typedef RS_B1<PlanNode_t, Operations_t> RS_B1_t;
typedef RS_B2<PlanNode_t, Operations_t> RS_B2_t;

typedef ExhaustiveTransformation<EquivalenceClass_t, EquivalenceClassIterator_t, PlanNode_t, Bitvector_t, Operations_t, Rule_t> ExhaustiveTransformation_t;

typedef BetterTransformation<PlanNode_t, Rule_t> BetterTransformation_t;



Operations_t * o = Operations_t::exemplar();

EquivalenceClass_t & join(EquivalenceClass_t e1, EquivalenceClass_t e2)
{
    return o->join(e1, e2);
}
EquivalenceClass_t & scan(unsigned int i)
{
    return o->scan(i);
}


#endif
