//
//  Types.h
//

#ifndef RuleBasedOptimizer_Types_h
#define RuleBasedOptimizer_Types_h

#include<stdint.h>
#include <initializer_list>

#include "PlanNode.h"
#include "BitvectorSmall.h"
#include "EquivalenceClass.h"
#include "ExhaustiveTransformation.h"
//#include "BetterTransformation.h"
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

typedef ExhaustiveTransformation<EquivalenceClass_t, EquivalenceClassIterator_t,
PlanNode_t, Bitvector_t, Operations_t, Rule_t> ExhaustiveTransformation_t;

//typedef BetterTransformation<PlanNode_t, Rule_t> BetterTransformation_t;



Operations_t * o = Operations_t::exemplar();

EquivalenceClass_t & scan(unsigned int i)
{
	return o->scan(i);
}

EquivalenceClass_t & join(EquivalenceClass_t e1, EquivalenceClass_t e2, Bitvector_t joinOn)
{
    return o->join(e1, e2, joinOn);
}

EquivalenceClass_t & join(EquivalenceClass_t e1, EquivalenceClass_t e2, std::initializer_list<unsigned int> aNeighborhood)
{
	Bitvector_t joinOn;
	for(unsigned int neighbor : aNeighborhood)
	{
		joinOn.set(neighbor);
	}
	return o->join(e1, e2, joinOn);
}

EquivalenceClass_t & join(unsigned int e1, unsigned int e2, std::initializer_list<unsigned int> aNeighborhood)
{
	Bitvector_t joinOn;
	for(unsigned int neighbor : aNeighborhood)
	{
		joinOn.set(neighbor);
	}
	return o->join(o->scan(e1), o->scan(e2), joinOn);
}

EquivalenceClass_t & join(EquivalenceClass_t e1, unsigned int e2, std::initializer_list<unsigned int> aNeighborhood)
{
	Bitvector_t joinOn;
	for(unsigned int neighbor : aNeighborhood)
	{
		joinOn.set(neighbor);
	}
	return o->join(e1, o->scan(e2), joinOn);
}

EquivalenceClass_t & join(unsigned int e1, EquivalenceClass_t e2, std::initializer_list<unsigned int> aNeighborhood)
{
	Bitvector_t joinOn;
	for(unsigned int neighbor : aNeighborhood)
	{
		joinOn.set(neighbor);
	}
	return o->join(o->scan(e1), e2, joinOn);
}





#endif
