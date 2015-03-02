//
//  PlanNode.h
//

#ifndef RuleBasedOptimizer_PlanNode_h
#define RuleBasedOptimizer_PlanNode_h

#include "Operator.h"
#include "EquivalenceClass.h"




/**
 * @brief Plan Node a node of a given plan
 * @details The plan node is used to connect up to 2 equivalence classes with each other
 *
 * @tparam Bitvector_t a new Bitvector
 */
template <typename Bitvector_t>
class PlanNode
{
	typedef PlanNode self_type;
	typedef EquivalenceClass<Bitvector_t, self_type> EquivalenceClass_t;
	struct Predicate
	{
		unsigned int _rightAttribute;
		unsigned int _leftAttribute;
	};
public:
	PlanNode(){ init(); };
	
	
	inline Bitvector_t getSignature() const { return _left->getRelations(); }
	
	Bitvector_t getRelations()
	{
		Bitvector_t b;
		b += _left->getRelations();
		if(_right != NULL)
			b += _right->getRelations();
		return b;
	}
	
	
	void set(Operator anOperator, EquivalenceClass_t * aLeftEC, EquivalenceClass_t * aRightEC)
	{
		_op = anOperator;
		_left = aLeftEC;
		_right = aRightEC;
	};
	
	self_type * getNext() const { return _next; }
	void setNext(self_type * aNode) {_next = aNode; };
	
	bool hasNext()
	{
		return _next != NULL;
	}
	
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
	
	
	bool hasLeft() { return _left != NULL; }
	bool hasRight() { return _right != NULL; }
	
	
	u_int getSize()
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
	
	inline Operator getOperator(){ return _op; };
	
	inline EquivalenceClass_t & getRight()
	{
		return * _right;
	}
	
	inline EquivalenceClass_t & getLeft()
	{
		return * _left;
	}
	
	inline self_type & on(unsigned int left, unsigned int right)
	{
		_predicate._leftAttribute = left;
		_predicate._rightAttribute = right;
		return * this;
	};
	
	inline unsigned int getLeftAttribute() const
	{
		return _predicate._leftAttribute;
	}
	
	inline unsigned int getRightAttribute() const
	{
		return _predicate._rightAttribute;
	}
	
private:
	void init()
	{
		_next = NULL;
		_left = NULL;
		_right = NULL;
		_predicate = Predicate();
	};
	Operator _op;
	self_type * _next;
	EquivalenceClass_t * _left;
	EquivalenceClass_t * _right;
	Bitvector_t * _relations;
	Predicate _predicate;
	
};



#endif
