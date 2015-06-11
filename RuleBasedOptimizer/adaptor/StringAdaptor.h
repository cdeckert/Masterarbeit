//
//  StringAdaptor.h
//

#ifndef RuleBasedOptimizer_StringAdaptor_h
#define RuleBasedOptimizer_StringAdaptor_h


#include <string>
#include <vector>
#include <unordered_map>

#include "Operations.h"



template <typename PlanNode_t>
class StringAdaptor
{
	typedef typename PlanNode_t::EquivalenceClass_t EquivalenceClass_t;
	typedef Operations<PlanNode_t> Operations_t;
	typedef std::unordered_map<unsigned int, EquivalenceClass_t *> RelationsMap_t;

public:
	StringAdaptor() {};
	EquivalenceClass_t *parse(std::string);
	std::string dump(EquivalenceClass_t *);

private:
	Operations_t *o = Operations_t::exemplar();
	RelationsMap_t relationMap;

	std::vector<std::string> writeString(EquivalenceClass_t *);
	std::string getBestPlan(EquivalenceClass_t *);

};


//
// Implemenetation
//

template <typename PlanNode_t>
std::string StringAdaptor<PlanNode_t>::getBestPlan(EquivalenceClass_t *input)
{
	if (input->getOperator() == Operator::SCAN)
	{
		int rel = input->getRel();
		std::string plan =  input->getOperatorAsString() + "(" + std::to_string(rel) + ")";
		return plan;
	}
	else
	{
		std::string result = "";
		result = input->getBest().getOperatorAsString() + "(" + getBestPlan(&input->getBest().l());
		if (input->getBest().hasRight())
		{
			result += "," + getBestPlan(&input->getBest().r());
		}
		result += ")";
		return result;

	}
};


template <typename PlanNode_t>
std::string StringAdaptor<PlanNode_t>::dump(EquivalenceClass_t *input)
{
	std::string result = "";

	std::vector<std::string> plans = writeString(input);

	for (std::string p : plans)
	{
		result += "\n" + p;
	}

	result += "\n\n****BEST PLAN: \n" + getBestPlan(input);
	return result;
}


template <typename PlanNode_t>
std::vector<std::string>
StringAdaptor<PlanNode_t>::writeString(EquivalenceClass_t *input)
{
	std::vector<std::string> plans;
	typedef typename EquivalenceClass_t::Iterator EItr;
	if (input != NULL && input->getOperator() == Operator::SCAN)
	{
		int rel = input->getRel();
		std::string plan =  input->getOperatorAsString() + "(" + std::to_string(rel) + ")";
		plans.push_back(plan);
	}
	else
	{
		for (EItr eq = input->begin(); eq.isOK(); ++eq)
		{

			{
				for (std::string left : writeString(& eq->l()))
				{

					for (std::string right : writeString(& eq->r()))
					{
						std::string plan = eq->getOperatorAsString() + "(" + left + "," + right + ")";
						plans.push_back(plan);
					}
				}
			}
		}
	}
	return plans;
}
#endif
