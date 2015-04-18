//
//  Statistics.h
//

#ifndef RuleBasedOptimizer_Statistics_h
#define RuleBasedOptimizer_Statistics_h

#include "Hasher.h"

template <typename Bitvector_t>
class Statistics
{
	std::unordered_map<Bitvector_t, double, Hasher<Bitvector_t>> _cardinality;
	std::unordered_map<Bitvector_t, double, Hasher<Bitvector_t>> _selectivity;

public:
	/**
	 * @brief [brief description]
	 * @details [long description]
	 */
	Statistics()
	{
		_selectivity.insert({
			{Bitvector_t(1), 0.5}, {Bitvector_t(2), 0.75}, {Bitvector_t(4), 0.25}, {Bitvector_t(8), 0.25}
		});
	};

	/**
	 * @brief [brief description]
	 * @details [long description]
	 *
	 * @param rel1 [description]
	 * @param rel2 [description]
	 *
	 * @return [description]
	 */
	double getSelectivity(PlanNode_t * pn)
	{
		double selectivity = 1.0;
		if(!pn->hasRight())
		{
			return selectivity;
		}
		
		for(u_int i = 0; i< pn->l().getRelations().capacity(); ++i)
		{
			for(u_int j = 0; j < pn->r().getRelations().capacity(); ++j)
			{
				Bitvector_t b;
				b.set(i);
				b.set(j);
				if(_selectivity.count(b) > 0)
				{
					selectivity *= _selectivity.at(b);
				}
				
			}
		}
			
		return selectivity;
	}
};

#endif
