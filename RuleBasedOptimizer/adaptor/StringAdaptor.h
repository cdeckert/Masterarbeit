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
    typedef Operations<PlanNode_t, unsigned int> Operations_t;
    typedef std::unordered_map<unsigned int, EquivalenceClass_t *>  RelationsMap_t;
    
public:
    
    StringAdaptor(){};
    EquivalenceClass_t * parse(std::string);
    std::string dump(EquivalenceClass_t *);
    
private:
    //RelationsMap_t getRelations(json11::Json);
    //EquivalenceClass_t * createJoinTree(json11::Json);
    std::vector<std::string> writeString(EquivalenceClass_t *);
    Operations_t * o = Operations_t::exemplar();
    RelationsMap_t relationMap;
    
};



/*template <typename PlanNode_t>
typename StringAdaptor<PlanNode_t>::RelationsMap_t StringAdaptor<PlanNode_t>::getRelations(json11::Json json)
{
    RelationsMap_t relations;
    
    for(json11::Json rel : json["relations"].array_items())
    {
        unsigned int relName = rel.int_value();
        relations.insert({{relName, o->rel(relName)}});
    }
    
    for(json11::Json edge : json["joinEdges"].array_items())
    {
        relations.at(edge["from"].int_value())->addNeighbor(edge["to"].int_value());
        relations.at(edge["to"].int_value())->addNeighbor(edge["from"].int_value());
    }
    return relations;
}*/



/*template <typename PlanNode_t>
typename StringAdaptor<PlanNode_t>::EquivalenceClass_t * StringAdaptor<PlanNode_t>::createJoinTree(json11::Json query)
{
    if(query["op"].string_value() == "scan")
    {
        return o->scan(* relationMap.at(query["l"].int_value()));
    }
    else
    {
        return o->join( * createJoinTree(query["l"]), * createJoinTree(query["r"]));
    }
}*/





/*
template <typename PlanNode_t>
typename StringAdaptor<PlanNode_t>::EquivalenceClass_t * StringAdaptor<PlanNode_t>::parse(std::string input){
    std::string err;
    json11::Json json = json11::Json::parse(input, err);
    std::cout << json.dump() << err;
    std::cout.flush();
    relationMap = getRelations(json);
    
    return createJoinTree(json["query"]);
}*/


template <typename PlanNode_t>
std::string StringAdaptor<PlanNode_t>::dump(EquivalenceClass_t * input){
    std::string result = "";
    
    std::vector<std::string> plans = writeString(input);
    for(std::string p : plans)
    {
        result += "\n" + p;
    }
    return result;
}


template <typename PlanNode_t>
std::vector<std::string> StringAdaptor<PlanNode_t>::writeString(EquivalenceClass_t * input)
{
    std::vector<std::string> plans;
    typedef typename EquivalenceClass_t::Iterator EItr;
    if(input->getOperator() == Operator::SCAN)
    {
        int rel = input->getRel();
        std::string plan =  input->getOperatorAsString() +"(" + std::to_string(rel) + ")";
        plans.push_back(plan);
    }
    else
    {
        for(EItr eq = input->begin(); eq.isOK(); ++eq)
        {
            
            {
                for(std::string left : writeString(& eq->l()))
                {
                    
                    for(std::string right : writeString(& eq->r()))
                    {
                        std::string plan = eq->getOperatorAsString() + "("+left + ","+right+")";
                        plans.push_back(plan);
                    }
                }
            }
        }
    }
    
    return plans;
}







#endif
