//
//  Hasher.h
//

#ifndef RuleBasedOptimizer_Hasher_h
#define RuleBasedOptimizer_Hasher_h

template<class Tbv>
class Hasher {
public:
    inline std::size_t operator()(const Tbv& aBv) const {
        return aBv.hashvalue();
    };
};

#endif
