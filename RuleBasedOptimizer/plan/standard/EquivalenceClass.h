//
//  EquivalenceClass.h
//

#ifndef RuleBasedOptimizer_EquivalenceClass_h
#define RuleBasedOptimizer_EquivalenceClass_h

#include <iterator>
#include <ostream>
#include <sstream>
#include <string>
#include <iostream>


#include "Reservoir.h"

/**
 * @brief Iterator to through each plan node
 * @details The iterator allows to iterate through all existing plan nodes
 *
 * @tparam PlanNode_t [description]
 */
template <typename PlanNode_t>
class EquivalenceClassIterator
{
	typedef EquivalenceClassIterator self_type;
	typedef typename PlanNode_t::Bitvector_t Bitvector_t;
	
	
public:
	EquivalenceClassIterator(PlanNode_t & aNode){ _node = &aNode; };
	
	/**
	 * @brief checks whether or not the next node is the last one
	 * @details chacks based on the current node if the next node is available
	 * @return true in case the next node is availiable
	 */
	inline const bool hasNext() const { return _node->hasNext(); };
	
	/**
	 * @brief checks wheather or not the current node can be used for 
	 * further operations
	 * @details checks if a given iterator points to a node
	 * @return true in case the current node is not NULL
	 */
	inline const bool isOK() const { return _node != NULL; };
	
	/**
	 * @brief accessor that returns the current node
	 * @return current node
	 */
	inline PlanNode_t * node(){ return _node; };
	
	/**
	 * @brief Increments iterator by 1
	 * @details replaces the current node with the next node
	 */
	inline self_type& operator++()
	{
		_node = _node->getNext();
		return *this;
	};
	
	/**
	 * @brief Convinience operator to access the node without calling node()
	 */
	inline PlanNode_t * operator->() const { return _node; };
	
private:
	PlanNode_t * _node;
};




/**
 * @brief [brief description]
 * @details [long description]
 *
 * @tparam Bitvector_t  [description]
 * @tparam PlanNode_t [description]
 */
template <typename PlanNode_t>
struct EquivalenceClass
{
	typedef EquivalenceClass self_type;
	typedef typename PlanNode_t::Bitvector_t Bitvector_t;
	typedef EquivalenceClassIterator<PlanNode_t> Iterator;
	typedef Reservoir<self_type> Reservoir_t;
	
	friend Iterator;
	
public:
	EquivalenceClass() { init(); };
	/**
	 * @brief iterator which references the first plan node
	 * @details the method references the first node of the equivalence class
	 * @return an iterator
	 */
	inline Iterator begin() const { return Iterator(*_first); };
	
	/**
	 * @brief Accessor for relations
	 * @details helps to access relations which are represented by the 
	 * equivalence class
	 * @return a bitvector
	 */
	inline Bitvector_t & getRelations() { return _relations; };
	
	
	void setRelations(Bitvector_t & aRelations) { _neighbors+=aRelations; }
	
	bool hasSameNeighbor(Bitvector_t b){ return _neighbors.contains(b); };
	
	
	void push_back(PlanNode_t & aPlanNode);

	
	std::ostream & print(std::ostream & os) const;
	std::ostream & printEndl(std::ostream & os) const;
	
	/**
	 * @brief setter for predicate attributes
	 * @details The setter for predicate attributes is mainly used to represent 
	 * database columns which are used to join relations based on them
	 * 
	 * @param left left relationship column
	 * @param right right relationship column
	 * 
	 * @return Equivalence class to allow method chaining 
	 */
	self_type & on(unsigned int left, unsigned right)
	{
		throwExceptionInCaseEqWasExpended();
		_first->on(left, right);
		return *this;
	}
	
	/**
	 * @brief Measures the number of all explored plans
	 * @return the number of already explored plans
	 */
	u_int getSize() const;
	
	u_int getCount() const;
	
	Bitvector_t & getSignature() { return _relations; };
	
	Operator getOperator() const
	{
		throwExceptionInCaseEqWasExpended();
		return _first->getOperator();
	};
	
	self_type & getLeft() const
	{
		throwExceptionInCaseEqWasExpended();
		return _first->getLeft();
	};
	
	/**
	 * @brief Accessor to get access to the first equivalenceclass
	 * @details [long description]
	 * 
	 * @param begin [description]
	 * @return [description]
	 */
	self_type & getRight() const
	{
		throwExceptionInCaseEqWasExpended();
		return _first->getRight();
	};
	
	/**
	 * @brief Accessor for predicate attributes
	 * 
	 * @return returns a number which represents a database column
	 */
	unsigned int getLeftAttribute() const
	{
		throwExceptionInCaseEqWasExpended();
		return _first->getLeftAttribute();
	};
	
	/**
	 * @brief Accessor for predicate attributes
	 * 
	 * @return returns a number which represents a database column
	 */
	unsigned int getRightAttribute() const
	{
		throwExceptionInCaseEqWasExpended();
		return _first->getRightAttribute();
	};
	
	
	
private:
	Bitvector_t _relations;
	Bitvector_t _neighbors;
	PlanNode_t * _first;
	PlanNode_t * _last;

	bool _explored;

	/**
	 * @brief initalizes values
	 * @details default init
	 */
	void init()
	{
		_first = NULL;
		_last = NULL;
		_explored = false;
	};

	/**
	 * @brief thows exception in case the eq was explored before
	 * @details In case the equivalence class was explored before it is not 
	 * possible to determin the "correct" left / right / operator because 
	 * a bunch of logical equal plans are in place
	 * 
	 */
	void throwExceptionInCaseEqWasExpended() const
	{
		if(_explored)
		{
			throw;
		}
	}
	
	
	bool hasPlanNodes() const { return _first != NULL; };
	
	void setNeighbors(Bitvector_t aNeighbor) { _neighbors += aNeighbor; }
};


/**
 *
 * Implementation
 *
 */


template <typename PlanNode_t>
void EquivalenceClass<PlanNode_t>::push_back(PlanNode_t & aPlanNode)
{
	if(_first == NULL)
	{
		_first = &aPlanNode;
		_last = &aPlanNode;
		_relations += _first->getRelations();
	}
	else
	{
		_explored = true;
		_last->setNext(&aPlanNode);
		_last = &aPlanNode;
		_relations += _last->getSignature();
	}
	
};

template <typename PlanNode_t>
u_int EquivalenceClass<PlanNode_t>::getSize() const
{
	u_int size = 0;
	for(Iterator itr = begin(); itr.isOK(); ++itr)
	{
		size += itr.node()->getSize();
	}
	
	return size;
};

template <typename PlanNode_t>
u_int EquivalenceClass<PlanNode_t>::getCount() const
{
	u_int count = 0;
	for(Iterator itr = begin(); itr.isOK(); ++itr)
	{
		count += itr.node().getCount();
	}
	return count;
};









template <typename PlanNode_t>
std::ostream & EquivalenceClass<PlanNode_t>::print(std::ostream & os) const
{
	if(hasPlanNodes())
	{
		for(Iterator itr = begin(); itr.isOK(); ++itr)
		{
			itr.node()->print(os);
		}
	}
	else
	{
		_relations.print2(os);
	}
	
	return os;
};


template <typename PlanNode_t>
std::ostream & EquivalenceClass<PlanNode_t>::printEndl(std::ostream & os) const
{
	int i = 0;
	if(hasPlanNodes())
	{
		for(Iterator itr = begin(); itr.isOK(); ++itr)
		{
			i++;
			os << i << ": ";
			itr.node()->print(os) << std::endl;
		}
	}
	else
	{
		_relations.print2(os);
	}
	
	return os;
};

#endif
