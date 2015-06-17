PlanNode *apply(PlanNode &aPlanNode, PlanNode &left, PlanNode &right) const override
{
	Bitvector_t js = merge(aPlanNode.l().getRelations(), aPlanNode.r().getRelations());
	BvSet_t partition = this->partition(js);
	EquivalenceClass_t *e = this->createTrees(partition, js);
	return e->getFirst();
};