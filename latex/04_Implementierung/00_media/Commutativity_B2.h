template <typename PlanNode_t, typename Operations_t>
class CommutativityRule_B2 : public CommutativityRule<PlanNode_t, Operations_t>
{
	typedef CommutativityRule<PlanNode_t, Operations_t> Parent_t;
public:
	bool isApplicable(PlanNode_t &aPlanNode, PlanNode_t &left, PlanNode_t &right) const override
	{
		return aPlanNode.isCommutativityEnabled() && Parent_t::isApplicable(aPlanNode, left, right);
	}
	PlanNode_t *apply(PlanNode_t &aPlanNode, PlanNode_t &left, PlanNode_t &right) const override
	{
		return Parent_t::apply(aPlanNode, left, right)->disableAllRules();
	};
};