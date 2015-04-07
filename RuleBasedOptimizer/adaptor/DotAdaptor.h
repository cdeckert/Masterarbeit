//
//  DotAdaptor.h
//

#ifndef RuleBasedOptimizer_DotAdaptor_h
#define RuleBasedOptimizer_DotAdaptor_h

template <typename PlanNode_t>
class DotAdaptor {
	typedef typename PlanNode_t::EquivalenceClass_t EquivalenceClass_t;
	typedef Operations<PlanNode_t, unsigned int> Operations_t;
	typedef std::unordered_map<unsigned int, EquivalenceClass_t *>  RelationsMap_t;
	
public:
	DotAdaptor(){};
	EquivalenceClass_t * parse(std::string);
	void nextToken();
	
private:
	enum TokenType{Delimiter, Relation, Edge, WhiteSpace};
	std::string token;
	std::string getShapes(EquivalenceClass_t *);
	
	std::string dump(EquivalenceClass_t *);
};


template <typename PlanNode_t>
void DotAdaptor<PlanNode_t>::nextToken()
{
	
};






#endif
