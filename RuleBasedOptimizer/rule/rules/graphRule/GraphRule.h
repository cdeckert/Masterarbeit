//
//  GraphRule.h
//

#ifndef RuleBasedOptimizer_GraphRule_h
#define RuleBasedOptimizer_GraphRule_h


/**
 * @brief Graph Rule
 * @details Rule that creates commutative plan nodes based on a given node
 *
 * @tparam PlanNode_t PlanNode
 * @tparam Operations_t basic operations like join and scan
 */
template <typename PlanNode, typename Operations_t>
class GraphRule : public Rule<PlanNode, Operations_t>
{
    
    
public:
    /**
     * @brief checks whether or not left associativity is applicable
     * @details left associativity is applicable in case the given operation is
     * "JOIN" the left descendant node is a join
     *
     * @param aPlanNode a given plan node
     * @return true in case the rule is applicable
     */
    bool isApplicable(PlanNode & aPlanNode) const override
    {
        // IF is Parent Node
        return aPlanNode.getOperator() == JOIN;
    };
    
    /**
     * @brief apply graph rule
     */
    PlanNode * apply(PlanNode & aPlanNode) const override
    {
        PlanNode * result = NULL;
        for(PlanNode & js_a : aPlanNode.l())
        {
            
            for(PlanNode & js_b : aPlanNode.r())
            {
                // PlanNode * js = merge(js_a, js_b);
                /*if(!aPlanNode.joinSet.contains(js))
                {
                    aPlanNode.joinSet.add(js);
                    
                }*/
            }
        }
        // for all js in aPlanNode.l()
            // for all js in aPlanNode.r()
            // js = merge(jsA, jsB)
            // if(aPlanNode.joinSet.contains(js)
                // aPlanNode.joinSet.add(js)
                // G = createGraph(js)
                // cuts = Partition(G)
                //trees.push_back(CreateTree(cuts))
        
        //return & this->o.joinPN(aPlanNode.l().l(), *this->o.join(aPlanNode.l().r(), aPlanNode.r()));
        return result;
    };
    
};




#endif
