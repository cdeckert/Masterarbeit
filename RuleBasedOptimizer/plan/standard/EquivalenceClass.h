//
//  EquivalenceClass.h
//

#ifndef RuleBasedOptimizer_EquivalenceClass_h
#define RuleBasedOptimizer_EquivalenceClass_h

#include <iterator>
#include <ostream>
#include <sstream>
#include <string>


#include "Reservoir.h"


/**
 * @brief custom planNode Iterator
 */
template <typename PlanNode_t>
struct IteratorPlanNode : public std::iterator<std::forward_iterator_tag, PlanNode_t>
{
public:
    IteratorPlanNode(PlanNode_t * node)
    {
        _node = node;
    };
    PlanNode_t* operator*()
    {
        return _node;
    };
    
    const IteratorPlanNode<PlanNode_t>& operator++()
    {
        if(_node != nullptr && _node != NULL && _node->_next != NULL)
        {
            _node = _node->_next;
            return *this;
        }
        else
        {
            _node = NULL;
            return *this;
        }
        
    };
    
    
    
    inline const bool isNext()
    {
        return _node != NULL;
    };
    
    inline bool operator!=(const IteratorPlanNode& x) const { return (_node != x._node); }
    inline PlanNode_t * operator->() const { return _node; }
    
    
    PlanNode_t * _node;

private:
};


/**
 * @brief collection of equivalent plan nodes
 *
 */
template <typename PlanNode_t, typename Bitvector_t>
struct EquivalenceClass
{
    typedef EquivalenceClass<PlanNode_t, Bitvector_t> self_type;
    typedef IteratorPlanNode<PlanNode_t> Iterator;

public:
    EquivalenceClass()
    {
        _begin = NULL;
        _end = NULL;
        abc = "def";
    };
    
    EquivalenceClass(self_type const & aEQ)
    {
        _begin = aEQ._begin;
        _end = aEQ._end;
    };
    
    
    Iterator begin() { return Iterator(_begin);};
    Iterator end() { return Iterator(_end);};
    
    void push_back(PlanNode_t & planNode)
    {
        if(_begin == NULL)
        {
            _begin = &planNode;
        }
        else
        {
            if(_end == NULL)
            {
                _end = _begin;
            }
            _end->_next = &planNode;
            _end = _end->_next;
        }
    };
    
    Bitvector_t & getRelations() const
    {
        return _begin->getRelations();
    };
    
    const u_int size()
    {
        u_int i = 0;
        for(Iterator itr = begin(); itr.isNext(); ++itr)
        {
            ++i;
        }
        return i;
    }
    
    const std::vector<self_type *> getChildECs()
    {
        std::vector<self_type *> eqs;
        for(Iterator itr = begin(); itr.isNext(); ++itr)
        {
            if(!itr->getLeft().isLeaf())
            {
                eqs.push_back(itr->getLeft().getEC());
            }
            if(itr->getRight().isLeaf())
            {
                eqs.push_back(itr->getRight().getEC());
            }
        }
        return eqs;
    };
    
    std::ostream& printFirst(std::ostream& os) const
    {
        if(_begin != NULL)
        {
            return _begin->print(os);
        }
        else
        {
            return os;
        }
        
    };
    
    PlanNode_t & node() { return *_begin; }
    
    
    inline std::vector<std::string> getStringVector()
    {
        std::vector<std::string> result;
        for(Iterator itr = begin(); itr.isNext(); ++itr)
        {
            for(std::string r : itr->getStringVector())
            {
                result.push_back(r);
            }
        }
        return result;
    }
    
    std::vector<std::string> printLevel()
    {
        std::vector<std::string> result;
        for(Iterator itr = begin(); itr.isNext(); ++itr)
        {
            std::stringstream ss;
            ss << "(" << itr->getLeft().getRelations() <<"," << itr->getRight().getRelations() << ")";
            result.push_back(ss.str());
        }
        return result;
    }
    
    PlanNode_t & getFirst()
    {
        return *_begin;
    }
        PlanNode_t * _begin;

private:
    PlanNode_t * _end;
    std::string abc;

};


#endif
