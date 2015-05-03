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
		while (c_prim != 0)
		{
			unsigned int index = leastSignificantSetBit(c_prim);
			c_prim = setunion(result, _neighborhood[index]);
		}
		return difference(result, c);
	};
	inline uint32_t difference(uint32_t x, uint32_t y) const { x &= (~y); return x;}
    inline uint32_t setunion(uint32_t x, uint32_t y) const { return x|y; };
	inline uint32_t intersect(uint32_t x, uint32_t y) const { x |= y; return x;}
	inline uint32_t reset(uint32_t x, unsigned int i) const { x &= ~(((uint32_t) 1) << i); return x;}
	inline uint32_t lowest_bit(uint32_t x) const { return (x & (-x)); }
	inline unsigned int leastSignificantSetBit(uint32_t x) const { return _bit_scan_forward(x); }
	inline unsigned int cardinality(uint32_t x) const { return pop64(x); }
	inline bool disjoint(uint32_t x, uint32_t y) const { return 0 == (x & y); }
	inline unsigned int pop64(uint32_t x) const {return x; }
    inline unsigned int _bit_scan_forward(uint32_t x) const {return x; }

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

	MinCutConservative(const uint32_t s, uint32_t const * neighborhood) : _s(s), _neighborhood(neighborhood), _stackIndex(0)
	{
		_state = 2;
		_hasNext = true;
		_s_card = cardinality(s);
		_stack = new stack_entry[_s_card];
		_stackPointer = &_stack[0];
		_stackPointer->c = 0;
		_stackPointer->neigh = lowest_bit(_s);
		_stackPointer->x = 0;
		_stackPointer->iter = _stackPointer->neigh;
		_stackIndex = 0;

		_bccStack = new uint32_t[(_s_card * (_s_card - 1)) / 2];
		_bccIndex = 0;
	}

	void next(uint32_t & left, uint32_t & right)
	{
		bool did_emit = false;
		while (true)
		{
			switch (_state)
			{
			case 1:
			{
				left = _stackPointer->c;
				right = difference(_s, left);
				did_emit = true;
			}
			case 2:
			{
				_stackPointer->iter = difference(_stackPointer->neigh, _stackPointer->x);
			}
			case 3:
			{
				if (_stackPointer->iter != 0)
				{
					uint32_t current = lowest_bit(_stackPointer->iter);
					uint32_t c_new = setunion(_stackPointer->c, current);

					uint32_t neigh_itr = intersect(difference(_neighborhood[leastSignificantSetBit(current)], c_new), _s);
					_stackPointer->neigh_new = difference(setunion(_stackPointer->neigh, neigh_itr), current);

					if (_stackPointer->neigh_new == 0)
					{
						_state = 5;
						break;
					}
					_stackPointer->c_new = c_new;
					_stackPointer->num_bccs_found = getConnectedComponents(_s, c_new, neigh_itr, _stackPointer->neigh_new);
					_stackPointer->num_bccs = _stackPointer->num_bccs_found;

					if ( _stackPointer->num_bccs_found == 0)
					{
						_stackIndex++;
						_stack[_stackIndex].num_bccs = 0;
						_stack[_stackIndex].c = c_new;
						_stack[_stackIndex].x = _stackPointer->x;
						_stack[_stackIndex].neigh = _stackPointer->neigh_new;
						_stackPointer->x = setunion(_stackPointer->x, current);
						_stackPointer = & _stack[_stackIndex];
						_state = 1;
						if (did_emit)
						{
							return;
						}
						else
						{
							_state = 5;
							break;
						}
					}
				}
			}
			case 4:
			{
				if (_stackPointer->num_bccs > 0)
				{
					_stackPointer->num_bccs--;
                    uint32_t c_jump = _bccStack[_bccIndex - _stackPointer->num_bccs];
                    uint32_t c_jump_no_c = difference(c_jump, _stackPointer->c);
                    uint32_t neigh_jump = setunion(intersect(getNeighbourhood(c_jump_no_c), _s), _stackPointer->neigh_new);
                    neigh_jump = difference(neigh_jump, c_jump);
                    if(disjoint(c_jump, _stackPointer->x) && c_jump < _s)
                    {
                        ++_stackIndex;
                        _stack[_stackIndex].num_bccs = 0;
                        _stack[_stackIndex].c = c_jump;
                        _stack[_stackIndex].x = _stackPointer->x;
                        _stack[_stackIndex].neigh = neigh_jump;
                        _stackPointer = &_stack[_stackIndex];
                        _state = 1;
                        if(did_emit)
                        {
                            return;
                        }
                        else
                        {
                            break;
                        }
    
                    }
                    else
                    {
                        _state = 4;
                        break;
                    }
				}
                else
                {
                    uint32_t current = lowest_bit(_stackPointer->iter);
                    _stackPointer->x = setunion(_stackPointer->x, current);
                    _bccIndex -= _stackPointer->num_bccs_found;
                    _stackPointer->iter = difference(_stackPointer->iter, current);
                    _state = 3;
                    break;
                }
                
			}
                case 5:
                {
                    --_stackIndex;
                    _stackPointer = &_stack[_stackIndex];
                    if(_stackIndex < 0)
                    {
                        _hasNext = false;
                        return;
                    }
                    if(_stackPointer->num_bccs_found == 0)
                    {
                        _stackPointer->iter = difference(_stackPointer->iter, lowest_bit(_stackPointer->iter));
                        _state = 3;
                    }
                    else
                    {
                        _state = 4;
                    }
                    break;
                }


			default:
				break;
			}
		}
	}



};

#endif
