//
//  PlanNode.h
//

#ifndef RuleBasedOptimizer_PlanNode_h
#define RuleBasedOptimizer_PlanNode_h

#include "Operator.h"
#include "EquivalenceClass.h"





/**
 * @brief Equivalence Class is a collection of equivalent PlanNodes
 */
template <typename Bitvector_t>
struct PlanNode
{
    typedef PlanNode<Bitvector_t> self_type;
    typedef EquivalenceClass<self_type, Bitvector_t> EquivalenceClass_t;
    
    /**
     * @brief combination of Euqivalence class and bitvector
     */
    struct Descendant
    {
        EquivalenceClass_t * _ec;
        const Bitvector_t & _relations;
        
    public:
        Descendant(const Bitvector_t & aBitvector) : _relations(aBitvector)
        {
            _ec = NULL;
        };
        Descendant(EquivalenceClass_t  & aEC) : _relations(aEC.getRelations())
        {
            _ec = &aEC;
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
    

public:
    
    static Descendant * getDescendant(EquivalenceClass_t aEQ){ return (new Descendant(aEQ)); };
    static Descendant * getDescendant(Bitvector_t aEQ){ return (new Descendant(aEQ)); };
    
    PlanNode(Operator op, const Descendant & aLeftDescendantNode, const Descendant & aRightDescendantNode) : _leftDecendent(aLeftDescendantNode), _rightDecendent(aRightDescendantNode), _op(op)
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
    
    
    
    
    inline const Descendant & getLeft() const
    {
        return _leftDecendent;
    }
    
    inline const Descendant & getRight() const
    {
        return _rightDecendent;
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
    
    

private:
    const Operator _op;
    const Descendant & _leftDecendent;
    const Descendant & _rightDecendent;

};




#endif
