//
//  JSONAdaptor.h
//

#ifndef RuleBasedOptimizer_JSONAdaptor_h
#define RuleBasedOptimizer_JSONAdaptor_h

#include <string>
#include <unordered_map>

#include "json11.hpp"
#include "Operations.h"



template <typename PlanNode_t>
class JSONAdaptor
{
    typedef typename PlanNode_t::EquivalenceClass_t EquivalenceClass_t;
    typedef Operations<PlanNode_t, unsigned int> Operations_t;
    typedef std::unordered_map<unsigned int, EquivalenceClass_t *>  RelationsMap_t;
    
public:
    
    JSONAdaptor(){};
    EquivalenceClass_t * parse(std::string);
    
private:
    RelationsMap_t getRelations(json11::Json);
    Operations_t * o = Operations_t::exemplar();
    
};



template <typename PlanNode_t>
typename JSONAdaptor<PlanNode_t>::RelationsMap_t JSONAdaptor<PlanNode_t>::getRelations(json11::Json json)
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
}









template <typename PlanNode_t>
typename JSONAdaptor<PlanNode_t>::EquivalenceClass_t * JSONAdaptor<PlanNode_t>::parse(std::string input){
    std::string err;
    json11::Json json = json11::Json::parse(input, err);
    std::cout << json.dump() << err;
    RelationsMap_t relationMap = getRelations(json);
    
    //std::string query = json["query"].string_value();
    
    
    
    
    
    return relationMap.at(1);
}


#endif
