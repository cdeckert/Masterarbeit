//
//  PlanNode.h
//

#ifndef RuleBasedOptimizer_PlanNode_h
#define RuleBasedOptimizer_PlanNode_h

#include "Operator.h"
#include "EquivalenceClass.h"


/**
 * @brief combination of Euqivalence class and bitvector
 */
template<typename Bitvector_t, typename EquivalenceClass_t>
struct Descendant
{
    EquivalenceClass_t * _ec;
public:
    const Bitvector_t & _relations;
    
    
    std::string abc;
    
public:
    Descendant(const Bitvector_t & aBitvector) : _relations(aBitvector)
    {
        _ec = NULL;
        abc = "abc";
    };
    Descendant(EquivalenceClass_t  & aEC) : _relations(aEC.getRelations())
    {
        _ec = &aEC;
         abc = "abc";
    };
    
    Descendant(EquivalenceClass_t  * aEC) : _relations(aEC->getRelations())
    {
        _ec = aEC;
        abc = "abc";
    };
    
    EquivalenceClass_t * getEC() const
    
    {
        return _ec;
    }
    
    
    
    Descendant(const Descendant  & aDecendant):_relations(aDecendant.getRelations())
    {
        _ec = &aDecendant.getEC();
    };
    
    const Bitvector_t & getRelations() const
    {
        return _relations;
    }
    
    
    inline bool isLeaf() const { return _ec == NULL; };
    inline const Descendant & getLeft() const { return _ec->node().getLeft(); }
    
    inline const Descendant & getRight() const
    {
        return _ec->node().getRight();
    }
    
    
    std::ostream & print(std::ostream & os) const
    {
        if(isLeaf())
        {
            os << _relations;
        }
        else
        {
            _ec->printFirst(os);
        }
        return os;
    }
};



/**
 * @brief Equivalence Class is a collection of equivalent PlanNodes
 */
template <typename Bitvector_t>
struct PlanNode
{
    typedef PlanNode<Bitvector_t> self_type;
    typedef EquivalenceClass<self_type, Bitvector_t> EquivalenceClass_t;
    typedef Descendant<Bitvector_t, EquivalenceClass_t> Decendant_t;
    

public:
    
    static Decendant_t * getDescendant(EquivalenceClass_t aEQ){ return (new Decendant_t(aEQ)); };
    static Decendant_t * getDescendant(Bitvector_t aEQ){ return (new Decendant_t(aEQ)); };
    
    PlanNode(Operator op, const Decendant_t & aLeftDescendantNode, const Decendant_t & aRightDescendantNode) : _leftDecendent(aLeftDescendantNode), _rightDecendent(aRightDescendantNode), _op(op)
    {
        init();
    };
    
    PlanNode(Operator op, const Decendant_t & aLeftDescendantNode, EquivalenceClass_t & aRightEquivalence) : _leftDecendent(aLeftDescendantNode), _rightDecendent(*(new Decendant_t(aRightEquivalence))), _op(op)
    {
        init();
    };
    
    PlanNode(Operator op, const EquivalenceClass_t & aLeftEquivalence, const Decendant_t & aRightDescendantNode) : _leftDecendent(*(new Decendant_t(aLeftEquivalence))), _rightDecendent(aRightDescendantNode), _op(op)
    {
        init();
    };
    
    
    inline void init()
    {
        _next = NULL;
    };

    

    
    inline Bitvector_t & getRelations()
    {
        Bitvector_t * b = new Bitvector_t();
        *b += _leftDecendent.getRelations();
        *b += _rightDecendent.getRelations();
        return *b;
    };
    
    
    
    
    inline std::ostream& print(std::ostream& os) const
    {
        os << _op << "(";
        _leftDecendent.print(os);
        os << ",";
        _rightDecendent.print(os);
        os << ")";
                      
        return os;
    };
    
    inline std::vector<std::string>getStringVector()
    {
        std::vector<std::string> result;
        for(std::string left : leftStringVector())
        {
            for(std::string right : rightStringVector())
            {
                std::stringstream ss;
                ss << "(" << left << "," << right << ")";
                result.push_back(ss.str());
            }
        }
        return result;
    };
    
    
    inline const Bitvector_t getSignature() const
    {
        return this->getLeft().getRelations();
    }
    
    
    
    
    inline const Decendant_t & getLeft() const
    {
        return _leftDecendent;
    }
    
    inline const Decendant_t & getRight() const
    {
        return _rightDecendent;
    }
    
    std::string str()
    {
        std::stringstream ss;
        ss << "(" << _leftDecendent.getRelations() << "," <<_rightDecendent.getRelations() << ")";
        return ss.str();
    }

private:
    inline std::vector<std::string> leftStringVector()
    {
        std::vector<std::string> result;
        /*if(_leftEC == NULL)
        {
            std::stringstream ss;
            ss << _left;
            
            result.push_back(ss.str());
        }
        else
        {
            for(std::string l : _leftEC->getStringVector())
            {
                result.push_back(l);
            }
        }*/
        return result;
    }
    
    inline std::vector<std::string> rightStringVector()
    {
        std::vector<std::string> result;
        /*if(_rightEC == NULL)
        {
            std::stringstream ss;
            ss << _right;
            
            result.push_back(ss.str());
        }
        else
        {
            for(std::string l : _rightEC->getStringVector())
            {
                result.push_back(l);
            }
        }*/
        return result;
    }
    
    
    
    

public:
    self_type * _next;
    
    
    const Decendant_t & _leftDecendent;

private:
    const Operator _op;
    const Decendant_t & _rightDecendent;

};




#endif
