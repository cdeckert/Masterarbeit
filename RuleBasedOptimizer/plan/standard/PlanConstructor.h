//
//  PlanConstructor.h
//

#ifndef RuleBasedOptimizer_PlanConstructor_h
#define RuleBasedOptimizer_PlanConstructor_h

#include "PlanNode.h"


template <typename PlanNode>
class PlanConstructor
{
	
public:
	EquivalenceClass_t * getSingleNode(unsigned int) const
	{
		EquivalenceClass_t * equivalenceClass = new EquivalenceClass_t();
		PlanNode * pn = new PlanNode();
		equivalenceClass.push_back();
		return equivalenceClass;
	};
};



#endif
