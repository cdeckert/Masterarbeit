bool isApplicable(PlanNode_t & parentNode, PlanNode_t & left, PlanNode_t & right) const override
{
	return parentNode.getOperator() == JOIN && left.getOperator() == JOIN && parentNode.r().isOverlapping(left.r());
}

PlanNode_t * apply(PlanNode_t & parentNode, PlanNode_t & left, PlanNode_t & right)  const override
{
	return & this->o.joinPN(left.l(), *this->o.join(left.r(), parentNode.r()));
};