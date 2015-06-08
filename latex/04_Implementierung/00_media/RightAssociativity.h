bool isApplicable(PlanNode_t & parentNode, PlanNode_t & left, PlanNode_t & right) const override
{
	return parentNode.getOperator() == JOIN && right.getOperator() == JOIN && parentNode.l().isOverlapping(right.l());
};

PlanNode_t * apply(PlanNode_t & parentNode, PlanNode_t & left, PlanNode_t & right)  const override
{
	return & this->o.joinPN(*this->o.join(parentNode.l(), right.l()), right.r());
};