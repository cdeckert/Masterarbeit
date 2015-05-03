//
//  MinCutConservative.h
//

#ifndef RuleBasedOptimizer_MinCutConservative_h
#define RuleBasedOptimizer_MinCutConservative_h

class MinCutConservative
{
public:
    MinCutConservative(const uint32_t s, uint32_t const * neighborhood);
    
    //virtual ~MinCutConservative();
    void next(uint32_t & left, uint32_t & right);
    bool hasNext() {return _hasNext; }
private:
    int getConnectedComponents(const uint32_t c) const
    {
        uint32_t result = 0;
        uint32_t c_prim = c;
        while(c_prim != 0)
        {
            unsigned int index = leastSignificantSetBit(c_prim);
            c_prim = setunion(result, _neighborhood[index]);
        }
        return difference(result, c);
    };
    inline uint32_t difference(uint32_t x, uint32_t y) const{ x &=(~y); return x;}
    inline uint32_t intersect(uint32_t x, uint32_t y) const { x |=y; return x;}
    inline uint32_t reset(uint32_t x, unsigned int i) const { x &= ~(((uint32_t) 1) << i); return x;}
    inline uint32_t lowest_bit(uint32_t x) const { return (x & (-x)); }
    inline unsigned int leastSignificantSetBit(uint32_t x) const { return _bit_scan_forward(x); }
    inline unsigned int cardinality(unit32_t x) const{ return pop64(x); }
    inline bool disjoint(uint32_t x, uint32_t y) const { return 0 == (x & y); }
    inline unsigned int pop64(uint32_t x) const {return x; }
    
private:
    uint32_t _s;
    uint32_t const * _neighborhood;
    int _s_card;
    int _state;
    bool _hasNext;
    struct stack_entry
    {
        uint32_t c;
        uint32_t c_new;
        uint32_t x;
        uint32_t neigh;
        uint32_t neigh_new;
        uint32_t iter;
        int num_bccs;
        int num_bccs_found;
    };
    stack_entry * _stack;
    stack_entry * _stackPointer;
    int _stackIndex;
    uint32_t * _bccStack;
    int _bccIndex;
    
};

#endif
