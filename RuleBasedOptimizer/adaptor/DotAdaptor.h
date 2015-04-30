//
//  DotAdaptor.h
//

#ifndef RuleBasedOptimizer_DotAdaptor_h
#define RuleBasedOptimizer_DotAdaptor_h

template <typename PlanNode_t>
class DotAdaptor
{
	typedef unsigned int u_int;
	typedef typename PlanNode_t::EquivalenceClass_t EquivalenceClass_t;
	typedef Operations<PlanNode_t, u_int> Operations_t;
	typedef std::unordered_map<u_int, EquivalenceClass_t *>  RelationsMap_t;

public:
	/**
	 * @brief [brief description]
	 * @details [long description]
	 */
	DotAdaptor() {};
	/**
	 * @brief [brief description]
	 * @details [long description]
	 *
	 * @param  [description]
	 * @return [description]
	 */
	EquivalenceClass_t *parse(std::string);
	/**
	 * @brief [brief description]
	 * @details [long description]
	 */
	void nextToken();

private:
	enum TokenType {Delimiter, Relation, Edge, WhiteSpace};
	std::string token;
	std::string getShapes(EquivalenceClass_t *);

	std::string dump(EquivalenceClass_t *);
};

//
// Implemenetation
//

template <typename PlanNode_t>
void DotAdaptor<PlanNode_t>::nextToken()
{

};
#endif
