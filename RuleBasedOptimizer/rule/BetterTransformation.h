//
//  BetterTransformation.h
//

#ifndef RuleBasedOptimizer_BetterTransformation_h
#define RuleBasedOptimizer_BetterTransformation_h

#include <unordered_map>


#include "Hasher.h"
#include "RuleSet.h"

template <typename PlanNode_t, typename Rule_t>
class BetterTransformation
{
	
public:
	
	typedef BetterTransformation self_type;
	typedef RuleSet<Rule_t> RuleSet_t;
	typedef typename PlanNode_t::EquivalenceClass_t EquivalenceClass_t;
	
	typedef typename EquivalenceClass_t::Iterator PlanIterator_t;
	
	typedef typename PlanNode_t::Bitvector_t Bitvector_t;

	typedef std::vector<EquivalenceClass_t> EquivalenceClassVector_t;
	
	BetterTransformation(RuleSet_t aRuleSet)
	{
		_rulset = aRuleSet;
	};
	
	
	
	
	
	void apply(EquivalenceClass_t & aEquivalenceClass)
	{
		toDoList.push_back(aEquivalenceClass);
		// as long as the given to do list isn't empty, work!
		for(unsigned int i = 0; i < toDoList.size(); ++i)
		{
			applyTransformation(toDoList.at(i));
		}
		toDoList.clear();
		knownPlans.clear();

	};
	
	
	
private:
	RuleSet_t _rulset;
	EquivalenceClassVector_t toDoList;
	std::unordered_map<Bitvector_t, PlanNode_t, Hasher<Bitvector_t>> knownPlans;
	
	void addChildEqsToToDoList(PlanNode_t aPlanNode)
	{
		if(aPlanNode.hasLeft())
		{
			toDoList.push_back(aPlanNode.getLeft());
		}
		
		if(aPlanNode.hasRight())
		{
			toDoList.push_back(aPlanNode.getRight());
		}
		
	};
	
	void applyTransformation(EquivalenceClass_t & eq)
	{
		std::unordered_set<Bitvector_t, Hasher<Bitvector_t>> eqExploredPlans;
		for(PlanIterator_t planItr = eq.begin(); planItr.isOK(); ++planItr)
		{
			PlanNode_t & plan = * planItr.node();
			for(unsigned int i = 0; i < _rulset._size; ++i)
			{
				Rule_t & r = * _rulset._rules[i];
				if(r.isApplicable(plan))
				{
					PlanNode_t * newPlan =  r.apply(plan);
					if(eqExploredPlans.count(newPlan->getSignature()) == 0)
					{
						eqExploredPlans.insert(newPlan->getSignature());
						
						eq.push_back(*newPlan);
						addChildEqsToToDoList(*newPlan);
					}
				}
			}
		}
	}
};

#endif
