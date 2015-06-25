//
//  JSONAdaptor.h
//

#ifndef RuleBasedOptimizer_JSONAdaptor_h
#define RuleBasedOptimizer_JSONAdaptor_h

#include <string>
#include <unordered_map>

#include "json11.hpp"
#include "Operations.h"

/**
 * @brief Adaptor to build a tree based on JSON
 * @details This adaptor is used to generate json based on a given JSON rep.
 *
 * @tparam PlanNode_t a Standard PlanNode
 */
template <typename PlanNode_t>
class JSONAdaptor
{
	typedef unsigned int u_int;
	typedef typename PlanNode_t::EquivalenceClass_t EquivalenceClass_t;
	typedef Operations<PlanNode_t> Operations_t;
	typedef std::unordered_map<u_int, EquivalenceClass_t *>  RelationsMap_t;

public:


	/**
	 * @brief Parsing a json-string and returns  a new initial tree
	 * @details Based on json-string the method returns a new Equivalence Class
	 *
	 * @param  a json reprsentation of a tree
	 * @return a tree which is part of a equivalence class
	 */
	EquivalenceClass_t *parse(std::string);

	/**
	 * @brief Dumping the data back
	 * @details Creates based on a given Equivalnceclass a json object
	 *
	 * @param t a given Equivalence Class
	 * @return a json object
	 */
	json11::Json dump(EquivalenceClass_t *);

private:
	RelationsMap_t getRelations(json11::Json);
	EquivalenceClass_t *createJoinTree(json11::Json);
	std::vector<json11::Json> writeJson(EquivalenceClass_t *);
	Operations_t *o = Operations_t::exemplar();
	RelationsMap_t relationMap;

};

//
// Implementation
//
template <typename PlanNode_t>
typename JSONAdaptor<PlanNode_t>::RelationsMap_t
JSONAdaptor<PlanNode_t>::getRelations(json11::Json json)
{
	RelationsMap_t relations;

	for (json11::Json rel : json["relations"].array_items())
	{
		unsigned int relName = rel.int_value();
		relations.insert({{relName, o->rel(relName)}});
	}

	for (json11::Json edge : json["joinEdges"].array_items())
	{
		relations.at(edge["from"].int_value())->addNeighbor(edge["to"].int_value());
		relations.at(edge["to"].int_value())->addNeighbor(edge["from"].int_value());
	}
	return relations;
};

template <typename PlanNode_t>
typename JSONAdaptor<PlanNode_t>::EquivalenceClass_t *
JSONAdaptor<PlanNode_t>::createJoinTree(json11::Json query)
{
	if (query["op"].string_value() == "scan")
	{
		return o->scan(* relationMap.at(query["l"].int_value()));
	}
	else
	{
		return o->join( * createJoinTree(query["l"]), * createJoinTree(query["r"]));
	}
};

template <typename PlanNode_t>
typename JSONAdaptor<PlanNode_t>::EquivalenceClass_t *
JSONAdaptor<PlanNode_t>::parse(std::string input)
{
	std::string err;
	json11::Json json = json11::Json::parse(input, err);
	std::cout << json.dump() << err;
	std::cout.flush();
	relationMap = getRelations(json);

	return createJoinTree(json["query"]);
};

template <typename PlanNode_t>
json11::Json JSONAdaptor<PlanNode_t>::dump(EquivalenceClass_t *input)
{
	json11::Json result;
	std::vector<json11::Json> plans = writeJson(input);
	result = json11::Json::array(plans);
	std::cout << result.dump();
	return result;
};

template <typename PlanNode_t>
std::vector<json11::Json>
JSONAdaptor<PlanNode_t>::writeJson(EquivalenceClass_t *input)
{
	std::vector<json11::Json> plans;
	typedef typename EquivalenceClass_t::Iterator EItr;
	if (input->getOperator() == Operator::SCAN)
	{
		int rel = input->getRel();
		json11::Json plan = json11::Json::object
		{
			{"op", input->getOperatorAsString()}, {"l", rel}
		};
		plans.push_back(plan);
	}
	else
	{
		for (EItr eq = input->begin(); eq.isOK(); ++eq)
		{

			{
				for (json11::Json left : writeJson(& eq->l()))
				{

					for (json11::Json right : writeJson(& eq->r()))
					{
						json11::Json plan = json11::Json::object{{"op", eq->getOperatorAsString()}, {"l", left}, {"r", right}};
						plans.push_back(plan);
					}
				}
			}
		}
	}

	return plans;
};
#endif
