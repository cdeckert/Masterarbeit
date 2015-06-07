bool isApplicable(PlanNode_t & aPlanNode, PlanNode_t & left, PlanNode_t & right) const override
{
	return aPlanNode.getOperator() != SCAN && aPlanNode.l().isOverlapping(aPlanNode.r());
}

PlanNode_t * apply(PlanNode_t & aPlanNode, PlanNode_t & left, PlanNode_t & right)  const override
{
	return & this->o.joinPN(aPlanNode.r(), aPlanNode.l());
}

