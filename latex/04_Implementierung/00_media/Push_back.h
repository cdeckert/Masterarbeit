template <typename PlanNode_t>
void EquivalenceClass<PlanNode_t>::push_back(PlanNode_t &aPlanNode)
{
	if (_first == NULL)
	{
		_first = &aPlanNode;
		_last = &aPlanNode;
		_relations = _relations.union_with( _first->getRelations());

		_neighbors = _neighbors.union_with(_first->getNeighbors());

		_neighbors.set_to_difference(_neighbors, _relations);
	}
	else
	{
		_explored = true;
		_last->setNext(& aPlanNode.getLast());
		_last = &aPlanNode;
		_relations = _relations.union_with(_last->getSignature());
	}
};