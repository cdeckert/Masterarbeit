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
template <typename Bitvector_t>
class PlanNode
{
	typedef PlanNode self_type;
	typedef unsigned int u_int;
	
public:
	struct Signature
	{
		Bitvector_t _left;
		Bitvector_t _right;
	};
	typedef Bitvector_t BV;
	typedef EquivalenceClass<self_type> EquivalenceClass_t;

	PlanNode();

	/**
	 * @brief return signature of a plan node
	 * @details based on relations (left)
	 * @return signature as a bitvector
	 */
	Bitvector_t getSignature() const;

	/**
	 * @brief returns relations associated
	 * @return all relations associated with the current plan node
	 */
	Bitvector_t getRelations() const;

	/**
	 * @brief [brief description]
	 * @details [long description]
	 * @return [description]
	 */
	Bitvector_t getNeighbors() const;
	
	PlanNode<Bitvector_t> & getLast();
	
	void setLast(self_type *);

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
	void set(Operator anOperator, EquivalenceClass_t *aLeftEC,
					EquivalenceClass_t *aRightEC);

	/**
	 * @brief Checks whether or not a the next node is filled
	 * (like  a linked list)
	 * @return true in case the next node is available
	 */
	bool hasNext() const;

	/**
	 * @brief sets the next node
	 *
	 * @param aNode the node which will be the next node
	 */
	void setNext(self_type *);
	
	inline void concat(self_type * next){ if(next != NULL) getLast().setNext(next); };
	
	
	inline Signature getSignature2() const { return _signature; };

	/**
	 * @brief Accessor for the next node
	 * @return a pointer to the next ndoe
	 */
	self_type *getNext() const;

	/**
	 * @brief prints nodes
	 *
	 * @param os stream which is used for printing the node structure
	 * @return a stream which can be used for method chaining
	 */
	std::ostream &print(std::ostream &os);

	/**
	 * @brief checks weather or not the left node exists
	 * @return true in case left is exists
	 */
	bool hasLeft() const;

	/**
	 * @brief checks weather or not the right node exists
	 * @return true in case right is exists
	 */
	bool hasRight() const;

	/**
	 * @brief Calculates size based on all subordinary nodes
	 * @details [long description]
	 *
	 * @return integer which represents the number of explored plans
	 */
	u_int getSize() const;

	/**
	 * @brief Accessor for operation (e.g. join)
	 * @return enum
	 */
	Operator getOperator() const;


	/**
	 * @brief Accessor for operation (e.g. join)
	 * @return operator string
	 */
	std::string getOperatorAsString() const;


	/**
	 * @brief Accessor for right equivalences
	 * @return pointer to right equivalence
	 */
	EquivalenceClass_t & getRight() const;

	/**
	 * @brief Accessor for right equivalences
	 * @return pointer to right equivalence
	 */
	EquivalenceClass_t & r() const;

	/**
	 * @brief Accessor for left equivalences
	 * @return pointer to left equivalence
	 */
	EquivalenceClass_t & getLeft() const;

	/**
	 * @brief Accessor for left equivalences
	 * @return pointer to left equivalence
	 */
	EquivalenceClass_t & l() const;
	
	
	void setLeft(EquivalenceClass_t * e){_left = e;};
	void setRight(EquivalenceClass_t * e){_right = e;};
	/**
	 * @brief disables all rules
	 * @details used by B2 rule set
	 */
	self_type *disableAllRules();

	/**
	 * @brief disables all rules and enables commutativity
	 * @details used by B2 rule set
	 */
	self_type *disableAllAndEnableCommutativity();


	/**
	 * @brief checks whether or not commutativity is enabled
	 * @details check is performed by B2 ruleset
	 * @return the value of the corresponding variable
	 */
	bool isCommutativityEnabled() const;

	/**
	 * @brief checks whether or not left associativity is enabled
	 * @details check is performed by B2 ruleset
	 * @return the value of the corresponding variable
	 */
	bool isLeftAssociativityEnabled() const;

	/**
	 * @brief checks whether or not right associativity is enabled
	 * @details check is performed by B2 ruleset
	 * @return the value of the corresponding variable
	 */
	bool isRightAssociativityEnabled() const;

	/**
	 * @brief checks whether or not exchange is enabled
	 * @details check is performed by B2 ruleset
	 * @return the value of the corresponding variable
	 */
	bool isExchangeEnabled() const;
	
	void debug() const;

private:
	Operator _op;
	self_type *_next;
	EquivalenceClass_t *_left;
	EquivalenceClass_t *_right;

	bool _commutativityEnabled = true;
	bool _leftAssociativityEnabled = true;
	bool _rightAssociativityEnabled = true;
	bool _exchangeEnabled = true;
	Signature _signature;
};

//
// Implementation
//

template <typename Bitvector_t>
std::string PlanNode<Bitvector_t>::getOperatorAsString() const
{
	return operatorname[_op];
};

template <typename Bitvector_t>
Bitvector_t PlanNode<Bitvector_t>::getSignature() const
{
	return _left->getRelations();
};

template <typename Bitvector_t>
void PlanNode<Bitvector_t>::debug() const
{
	std::cout << "=== PlanNode ===" << std::endl;
	std::cout << "Relations:	" << getRelations() << std::endl;
	std::cout << "Neighborhood:	" << getNeighbors() << std::endl << std::endl;
	
};

template <typename Bitvector_t>
Bitvector_t PlanNode<Bitvector_t>::getRelations() const
{
	Bitvector_t b;
	b += _left->getRelations();
	if (_right != NULL)
	{
		b += _right->getRelations();
	}
	return b;
};

template <typename Bitvector_t>
void PlanNode<Bitvector_t>::set(Operator anOperator, EquivalenceClass_t *aLeftEC,
								EquivalenceClass_t *aRightEC)
{
	_op = anOperator;
	_left = aLeftEC;
	_right = aRightEC;
	_signature._left = _left->getRelations();
	if(_right != NULL)
	{
		_signature._right = _right->getRelations();
	}
};

template <typename Bitvector_t>
Bitvector_t PlanNode<Bitvector_t>::getNeighbors() const
{
	Bitvector_t b;
	b += _left->getNeighbors();
	if (_right != NULL)
		b += _right->getNeighbors();
	return b;
};

template <typename Bitvector_t>
PlanNode<Bitvector_t>::PlanNode()
{
	_next = NULL;
	_left = NULL;
	_right = NULL;
};

template <typename Bitvector_t>
bool PlanNode<Bitvector_t>::hasNext() const
{
	return _next != NULL;
};

template <typename Bitvector_t>
void PlanNode<Bitvector_t>::setNext(self_type * aNode)
{
	_next = aNode;
};

template <typename Bitvector_t>
PlanNode<Bitvector_t> * PlanNode<Bitvector_t>::getNext() const
{
	return _next;
};

template <typename Bitvector_t>
PlanNode<Bitvector_t> & PlanNode<Bitvector_t>::getLast()
{
	if(this->hasNext())
	{
		return this->_next->getLast();
	}
	else
	{
		return * this;
	}
	
};


template <typename Bitvector_t>
std::ostream &PlanNode<Bitvector_t>::print(std::ostream &os)
{
	if (_op == JOIN)
	{
		os << "JOIN";
	}
	else
	{
		os << "SCAN";
	}
	os << "(";

	if (_left != NULL)
	{
		_left->print(os);
	}

	if (_right != NULL)
	{
		os << ",";
		_right->print(os);
	}

	os << ")";
	return os;
};

template <typename Bitvector_t>
bool PlanNode<Bitvector_t>::hasLeft() const
{
	return _left != NULL;
};

template <typename Bitvector_t>
bool PlanNode<Bitvector_t>::hasRight() const
{
	return _right != NULL;
};

template <typename Bitvector_t>
typename PlanNode<Bitvector_t>::u_int PlanNode<Bitvector_t>::getSize() const
{
	if (_op == SCAN)
	{
		return 0;
	}
	if (_op == JOIN)
	{
		u_int size = 0;
		size += _left->getSize();
		size += _right->getSize();
		if (size == 0) return 1;
		return size;
	}
	return 0;
};

template <typename Bitvector_t>
Operator PlanNode<Bitvector_t>::getOperator() const
{
	return _op;
};

template <typename Bitvector_t>
typename PlanNode<Bitvector_t>::EquivalenceClass_t & PlanNode<Bitvector_t>::getRight() const
{
	return * _right;
};

template <typename Bitvector_t>
typename PlanNode<Bitvector_t>::EquivalenceClass_t & PlanNode<Bitvector_t>::getLeft() const
{
	return * _left;
};

template <typename Bitvector_t>
typename PlanNode<Bitvector_t>::EquivalenceClass_t & PlanNode<Bitvector_t>::r() const
{
	return getRight();
};

template <typename Bitvector_t>
typename PlanNode<Bitvector_t>::EquivalenceClass_t & PlanNode<Bitvector_t>::l() const
{
	return getLeft();
};

template <typename Bitvector_t>
typename PlanNode<Bitvector_t>::self_type * PlanNode<Bitvector_t>::disableAllRules()
{
	_commutativityEnabled = false;
	_leftAssociativityEnabled = false;
	_rightAssociativityEnabled = false;
	_exchangeEnabled = false;
	return this;
};

template <typename Bitvector_t>
typename PlanNode<Bitvector_t>::self_type * PlanNode<Bitvector_t>::disableAllAndEnableCommutativity()
{
	disableAllRules();
	_commutativityEnabled = true;
	return this;
};

template <typename Bitvector_t>
bool PlanNode<Bitvector_t>::isCommutativityEnabled() const
{
	return _commutativityEnabled;
};

template <typename Bitvector_t>
bool PlanNode<Bitvector_t>::isLeftAssociativityEnabled() const
{
	return _leftAssociativityEnabled;
};

template <typename Bitvector_t>
bool PlanNode<Bitvector_t>::isRightAssociativityEnabled() const
{
	return _rightAssociativityEnabled;
};

template <typename Bitvector_t>
bool PlanNode<Bitvector_t>::isExchangeEnabled() const
{
	return _exchangeEnabled;
};
#endif
