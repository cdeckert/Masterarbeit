//
//  Operations.h
//

#ifndef RuleBasedOptimizer_Operations_h
#define RuleBasedOptimizer_Operations_h

/**
 * @brief The operations class offers convinient access to basic operations
 * @details The operations class is used to execute methods like Join or scan.
 * The methods are using reservoirs to reduce the effort for instanciation of
 * new objects.
 *
 * @tparam Bitvector_t the standard Bitvector
 * @tparam EquivalenceClass_t the equivalence class
 * @tparam PlanNode_t the standard plan Node
 */

#include "Reservoir.h"
#include "Operator.h"


template <typename PlanNode_t>
class Operations
{
	typedef Operations self_type;
	typedef unsigned int u_int;
	typedef typename PlanNode_t::BV Bitvector_t;
	typedef typename PlanNode_t::EquivalenceClass_t EquivalenceClass_t;

public:
	static self_type *exemplar();

	/**
	 * @brief Constructor to create a bunch of reservoirs
	 * @details standard constructor runs more specific constructors with default values
	 */
	Operations() : Operations(300) {};
	/**
	 * @brief Constructor to create a bunch of reservoirs
	 * @details Initalizes a bunch of reservoirs based on a given number of expected objects
	 *
	 * @param  number of expected objects
	 */
	Operations(int);
	~Operations();
	
	/**
	 * @brief copy constructor
	 * @details copy constructor to copy operations
	 *
	 * @param copy construct
	 */
	Operations(const Operations &);

	/**
	 * @brief returns new and initalized bitvector
	 * @details returns a new bitvector instance and flips a bit
	 * at a specific position
	 *
	 * @param i position of the flipped bit
	 * @return Bitvector
	 */
	Bitvector_t *getBitVector(u_int i) const
	{
		Bitvector_t *b = _bitvectors->get_new_entry();
		b->set(i);
		return b;
	};

	/**
	 * @brief creates a equivalence class, which represents a scan operation
	 * @details creates a equivalence class, which includes a PlanNode
	 * (operation = scan) and a scanned relation
	 *
	 * @param the scanned relation
	 * @return a new EquivalenceClass
	 */
	EquivalenceClass_t *scan(EquivalenceClass_t &) const;

	/**
	 * @brief Creates a relation node based on a given bitvector
	 * @details Creates a new Equivalence Class relation node
	 *
	 * @param bitvector which represents a relation
	 * @return a new EquivalenceClass
	 */
	EquivalenceClass_t *rel1(Bitvector_t &b) const;

	/**
	 * @brief Create a scan Equivalence Node based on a given bitvector
	 * @details Create a new Equivalence Class which is the result of a scan
	 *
	 * @param bitvector
	 * @return a new EquivalenceClass
	 */
	EquivalenceClass_t *scan(Bitvector_t b) const;

	/**
	 * @brief Creates a new relational node
	 * @details Creates a new relational node based on a number
	 *
	 * @param i a given number
	 * @return a new Equivalence Node
	 */
	EquivalenceClass_t *rel(u_int i) const;

	/*EquivalenceClass_t * rel(Bitvector_t b)
	{
	    EquivalenceClass_t * eqN = reservoirEC->get_new_entry();
	    eqN->setRelations(b);
	    return eqN;
	}*/



	EquivalenceClass_t *rel(u_int i, std::initializer_list<u_int> neighbors) const;


	/**
	 * @brief Creates a planNode, which represents a join operation
	 * to initalize the predicate, please use the "on" method
	 *
	 * @param e1 Left relation
	 * @param e2 Right relation
	 *
	 * @return plan node with a single plan
	 */
	PlanNode_t &joinPN(EquivalenceClass_t &e1, EquivalenceClass_t &e2) const;


	/**
	 * @brief Creates a Equivalence Class which represents a join operation
	 * @details The Equivalence class is initalized with a simple plan (operation Join)
	 * to initalize the predicate, please use the "on" method
	 *
	 * @param e1 Left relation
	 * @param e2 Right relation
	 * @param joinOnRelations neighborhood
	 *
	 * @return equivalence class with a single plan
	 */
	EquivalenceClass_t *join(EquivalenceClass_t &e1, EquivalenceClass_t &e2) const;

	/**
	 * @brief returns a new bitvector from a reservoir
	 * @details return a bitvector
	 * @return bitvector
	 */

private:
	Reservoir<EquivalenceClass_t> *_reservoirEC;
	Reservoir<Bitvector_t> *_bitvectors;
	Reservoir<PlanNode_t> *_reservoirPN;
	static self_type *_instance;

};

//
// Implementation
//


// static
template <typename PlanNode_t>
Operations<PlanNode_t> *Operations<PlanNode_t>::_instance;


template <typename PlanNode_t>
Operations<PlanNode_t> *Operations<PlanNode_t>::exemplar()
{
	if (_instance == NULL)
	{
		_instance = new Operations();
	}
	return _instance;
}


// public
template <typename PlanNode_t>
Operations<PlanNode_t>::Operations(int reservoirSite)
{
	_reservoirEC = new Reservoir<EquivalenceClass_t>(reservoirSite * 2);
	_reservoirPN = new Reservoir<PlanNode_t>(reservoirSite);
	_bitvectors = new Reservoir<Bitvector_t>(reservoirSite);
};

template <typename PlanNode_t>
Operations<PlanNode_t>::~Operations()
{
	delete _reservoirEC;
	delete _reservoirPN;
	delete _bitvectors;
};

template <typename PlanNode_t>
typename Operations<PlanNode_t>::EquivalenceClass_t *Operations<PlanNode_t>::scan(EquivalenceClass_t &relation) const
{
	PlanNode_t &t = * _reservoirPN->get_new_entry();
	t.set(SCAN, &relation, NULL);
	EquivalenceClass_t *eq = _reservoirEC->get_new_entry();
	eq->push_back(t);
	return eq;
};

template <typename PlanNode_t>
typename Operations<PlanNode_t>::EquivalenceClass_t *Operations<PlanNode_t>::rel1(Bitvector_t &b) const
{
	EquivalenceClass_t *eqN = _reservoirEC->get_new_entry();
	eqN->setRelations(b);
	return eqN;
};

template <typename PlanNode_t>
typename Operations<PlanNode_t>::EquivalenceClass_t *Operations<PlanNode_t>::scan(Bitvector_t b) const
{
	EquivalenceClass_t *relation = rel1(b);
	return scan(*relation);
};

template <typename PlanNode_t>
typename Operations<PlanNode_t>::EquivalenceClass_t *Operations<PlanNode_t>::rel(u_int i) const
{
	Bitvector_t *b = getBitVector(i);
	EquivalenceClass_t *eqN = _reservoirEC->get_new_entry();
	eqN->setRelations(*b);
	return eqN;
}

template <typename PlanNode_t>
typename Operations<PlanNode_t>::EquivalenceClass_t *Operations<PlanNode_t>::rel(u_int i, std::initializer_list<u_int> neighbors) const
{
	Bitvector_t *b = getBitVector(i);
	Bitvector_t *neighbors_bit = _bitvectors->get_new_entry();
	for (u_int n : neighbors)
	{
		neighbors_bit->set(n);
	}
	EquivalenceClass_t *eqN = _reservoirEC->get_new_entry();
	eqN->setRelations(*b);
	eqN->setNeighbors(*neighbors_bit);
	return eqN;
}

template <typename PlanNode_t>
PlanNode_t &Operations<PlanNode_t>::joinPN(EquivalenceClass_t &e1, EquivalenceClass_t &e2) const
{
	PlanNode_t &t = * _reservoirPN->get_new_entry();
	t.set(JOIN, &e1, &e2);
	return t;
}

template <typename PlanNode_t>
typename Operations<PlanNode_t>::EquivalenceClass_t *Operations<PlanNode_t>::join(EquivalenceClass_t &e1, EquivalenceClass_t &e2) const
{

	PlanNode_t &t = joinPN(e1, e2);
	EquivalenceClass_t   *eq = _reservoirEC->get_new_entry();
	eq->push_back(t);
	return eq;
}





#endif
