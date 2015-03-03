//
//  PlanNode.h
//

#ifndef RuleBasedOptimizer_PlanNode_h
#define RuleBasedOptimizer_PlanNode_h

#include "Operator.h"
#include "EquivalenceClass.h"




/**
 * @brief Plan Node a node of a given plan
 * @details The plan node is used to connect up to 2 equivalence 
 * classes with each other
 *
 * @tparam Bitvector_t a new Bitvector
 */
template <typename Bitvector>
class PlanNode
{
	
	/**
	 * @brief Predicate represents in a join the predicate attribute
	 * @details Join on LEFT = RIght
	 */
	struct Predicate
	{
		unsigned int _rightAttribute;
		unsigned int _leftAttribute;
	};
public:
	typedef PlanNode self_type;
	typedef Bitvector Bitvector_t;
	typedef EquivalenceClass<self_type> EquivalenceClass_t;

	PlanNode(){ init(); };
	
	/**
	 * @brief return signature of a plan node 
	 * @details based on relations (left)
	 * @return signature as a bitvector
	 */
	inline Bitvector_t getSignature() const { return _left->getRelations(); }
	
	/**
	 * @brief returns relations associated
	 * @return all relations associated with the current plan node
	 */
	Bitvector_t getRelations() const
	{
		Bitvector_t b;
		b += _left->getRelations();
		if(_right != NULL)
			b += _right->getRelations();
		return b;
	}
	
	/**
	 * @brief sets operators and left and right equivalence for a new plan node
	 * @details the method is called only once to set left and right 
	 * euqivalences
	 * 
	 * @param anOperator e.g. join, scan
	 * @param aLeftEC equivalence which represents the left part of a join/scan
	 * @param aRightEC equivalence which represents the right part of a join
	 * the parameter can be null
	 */
	inline void set(Operator anOperator, EquivalenceClass_t * aLeftEC,
					EquivalenceClass_t * aRightEC)
	{
		_op = anOperator;
		_left = aLeftEC;
		_right = aRightEC;
	};
	



	/**
	 * @brief Checks whether or not a the next node is filled
	 * (like  a linked list)
	 * @return true in case the next node is available
	 */
	bool hasNext() const
	{
		return _next != NULL;
	}

	/**
	 * @brief sets the next node
	 *
	 * @param aNode the node which will be the next node
	 */
	void setNext(self_type * aNode) {_next = aNode; };
	
	/**
	 * @brief Accessor for the next node
	 * @return a pointer to the next ndoe
	 */
	inline self_type * getNext() const { return _next; }
	
	/**
	 * @brief prints nodes
	 * 
	 * @param os stream which is used for printing the node structure
	 * @return a stream which can be used for method chaining
	 */
	std::ostream & print(std::ostream & os)
	{
		if(_op == JOIN)
		{
			os << "JOIN";
		}
		else
		{
			os << "SCAN";
		}
		os << "(";
		
		if(_left != NULL)
		{
			_left->print(os);
		}
		
		if(_right != NULL)
		{
			os << ",";
			_right->print(os);
		}
		
		os << ")";
		return os;
	}
	
	/**
	 * @brief checks weather or not the left node exists
	 * @return true in case left is exists
	 */
	bool hasLeft() const { return _left != NULL; }

	/**
	 * @brief checks weather or not the right node exists
	 * @return true in case right is exists
	 */
	bool hasRight() const { return _right != NULL; }
	
	/**
	 * @brief Calculates size based on all subordinary nodes
	 * @details [long description]
	 * 
	 * @return integer which represents the number of explored plans
	 */
	u_int getSize() const
	{
		if(_op == SCAN)
		{
			return 0;
		}
		if(_op == JOIN)
		{
			u_int size = 0;
			size += _left->getSize();
			size += _right->getSize();
			if(size == 0) return 1;
			return size;
		}
		return 0;
		
	}

	/**
	 * @brief Accessor for operation (e.g. join)
	 * @return enum
	 */
	inline Operator getOperator()const { return _op; };
	

	/**
	 * @brief Accessor for right equivalences
	 * @return pointer to right equivalence
	 */
	inline EquivalenceClass_t & getRight() const
	{
		return * _right;
	}
	
	/**
	 * @brief Accessor for left equivalences
	 * @return pointer to left equivalence
	 */
	inline EquivalenceClass_t & getLeft() const
	{
		return * _left;
	}
	
	/**
	 * @brief Represents the "on" part of a given join operation
	 * @detail the predicate of a given join is set by this method
	 * 
	 * @param int left attribute
	 * @param int right attribute
	 * 
	 * @return existing plan node for Method chaining
	 */
	inline self_type & on(unsigned int left, unsigned int right)
	{
		_predicate._leftAttribute = left;
		_predicate._rightAttribute = right;
		return * this;
	};
	
	/**
	 * @brief Accessor for predicate attributes
	 * @details Assessor for predicate attribute (right)
	 * @return a number which represents the field which is used as 
	 * a join predicate attribute
	 */
	inline unsigned int getLeftAttribute() const
	{
		return _predicate._leftAttribute;
	}

	/**
	 * @brief Accessor for predicate attributes
	 * @details Assessor for predicate attribute (right)
	 * @return a number which represents the field which is used as 
	 * a join predicate attribute
	 */
	inline unsigned int getRightAttribute() const
	{
		return _predicate._rightAttribute;
	}
	
	/**
	 * @brief disables all rules
	 * @details used by B2 rule set
	 */
	inline void disableAllRules()
	{
		_commutativityEnabled = false;
		_leftAssociativityEnabled = false;
		_rightAssociativityEnabled = false;
		_exchangeEnabled = false;
	};
	
	/**
	 * @brief disables all rules and enables commutativity
	 * @details used by B2 rule set
	 */
	inline void disableAllAndEnableCommutativity()
	{
		disableAllRules();
		_commutativityEnabled = true;
	};
	

	/**
	 * @brief checks whether or not commutativity is enabled
	 * @details check is performed by B2 ruleset
	 * @return the value of the corresponding variable
	 */
	inline bool isCommutativityEnabled() const
	{ return _commutativityEnabled; };

	/**
	 * @brief checks whether or not left associativity is enabled
	 * @details check is performed by B2 ruleset
	 * @return the value of the corresponding variable
	 */
	inline bool isLeftAssociativityEnabled() const
	{ return _leftAssociativityEnabled; };

	/**
	 * @brief checks whether or not right associativity is enabled
	 * @details check is performed by B2 ruleset
	 * @return the value of the corresponding variable
	 */
	inline bool isRightAssociativityEnabled() const
	{ return _rightAssociativityEnabled; };

	/**
	 * @brief checks whether or not exchange is enabled
	 * @details check is performed by B2 ruleset
	 * @return the value of the corresponding variable
	 */
	inline bool isExchangeEnabled() const
	{ return _exchangeEnabled; };
	
	
	
private:
	
	Operator _op;
	self_type * _next;
	EquivalenceClass_t * _left;
	EquivalenceClass_t * _right;
	Bitvector_t * _relations;
	Predicate _predicate;
	
	bool _commutativityEnabled = true;
	bool _leftAssociativityEnabled = true;
	bool _rightAssociativityEnabled = true;
	bool _exchangeEnabled = true;

	/**
	 * @brief Initalizes all variables
	 * @details Standard init method
	 */
	void init()
	{
		_next = NULL;
		_left = NULL;
		_right = NULL;
		_predicate = Predicate();
	};
	

	
};



#endif
