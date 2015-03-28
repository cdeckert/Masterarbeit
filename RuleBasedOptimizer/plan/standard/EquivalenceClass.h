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
	
	inline Bitvector_t & getNeighbors() {return _neighbors; };
	
	/**
	 * @brief [brief description]
	 * @details [long description]
	 * 
	 * @param aRelations [description]
	 */
	void setRelations(Bitvector_t & aRelations) { _relations+=aRelations; }
	
	/**
	 * @brief [brief description]
	 * @details [long description]
	 * 
	 * @param b [description]
	 * @return [description]
	 */
	bool isOverlapping(Bitvector_t b){ return _relations.overlap(b); };
	
	/**
	 * @brief [brief description]
	 * @details [long description]
	 * 
	 * @param b [description]
	 * @return [description]
	 */
	bool isOverlapping(self_type b){ return _neighbors.overlap(b.getRelations()); };
	
	/**
	 * @brief [brief description]
	 * @details [long description]
	 * 
	 * @param aPlanNode [description]
	 */
	void push_back(PlanNode_t & aPlanNode);

	/**
	 * @brief [brief description]
	 * @details [long description]
	 * 
	 * @param os [description]
	 * @return [description]
	 */
	std::ostream & print(std::ostream & os) const;

	/**
	 * @brief [brief description]
	 * @details [long description]
	 * 
	 * @param os [description]
	 * @return [description]
	 */
	std::ostream & printEndl(std::ostream & os) const;
	
	
	/**
	 * @brief Measures the number of all explored plans
	 * @return the number of already explored plans
	 */
	u_int getSize() const;
	
	/**
	 * @brief [brief description]
	 * @details [long description]
	 * @return [description]
	 */
	u_int getCount() const;
	
	/**
	 * @brief [brief description]
	 * @details [long description]
	 * @return [description]
	 */
	Bitvector_t & getSignature() { return _relations; };
	
	/**
	 * @brief [brief description]
	 * @details [long description]
	 * 
	 * @param d [description]
	 * @return [description]
	 */
	Operator getOperator() const
	{
		throwExceptionInCaseEqWasExpended();
		return _first->getOperator();
	};
	
	/**
	 * @brief Accessor for operation (e.g. join)
	 * @return operator string
	 */
	inline std::string getOperatorAsString()const { throwExceptionInCaseEqWasExpended();
		return _first->getOperatorAsString(); };
	
	/**
	 * @brief [brief description]
	 * @details [long description]
	 * 
	 * @param d [description]
	 * @return [description]
	 */
	self_type & getLeft() const
	{
		throwExceptionInCaseEqWasExpended();
		return _first->getLeft();
	};
	
	/**
	 * @brief [brief description]
	 * @details [long description]
	 */
	self_type & l() const { return getLeft(); };
	
	/**
	 * @brief Accessor to get access to the first equivalenceclass
	 * @details [long description]
	 * 
	 * @param begin [description]
	 * @return [description]
	 */
	inline self_type & getRight() const
	{
		throwExceptionInCaseEqWasExpended();
		return _first->getRight();
	};
	
	/**
	 * @brief [brief description]
	 * @details [long description]
	 * 
	 * @param _relations [description]
	 * @return [description]
	 */
	inline unsigned int getRel()
	{
		return _relations.log2();
	}
	
	/**
	 * @brief [brief description]
	 * @details [long description]
	 */
	inline self_type & r() const { return getRight(); };
	
	/**
	 * @brief [brief description]
	 * @details [long description]
	 * 
	 * @param neighbors [description]
	 */
	void setNeighbors(Bitvector_t & neighbors) { _neighbors=neighbors; }
	
	/**
	 * @brief [brief description]
	 * @details [long description]
	 * 
	 * @param neighbor [description]
	 */
	void addNeighbor(u_int neighbor){ _neighbors.set(neighbor); };
	
	/**
	 * @brief [brief description]
	 * @details [long description]
	 * @return [description]
	 */
	bool hasPlanNodes() const { return _first != NULL; };
	
	/**
	 * @brief [brief description]
	 * @details [long description]
	 * @return [description]
	 */
	PlanNode_t * getFirst(){ return _first; };
	
	
private:
	Bitvector_t _neighbors;
	Bitvector_t _relations;
	
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
			//throw;
		}
	}
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
		_neighbors += _first->getNeighbors();
		_neighbors.set_to_difference(_neighbors, _relations);
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




#endif
