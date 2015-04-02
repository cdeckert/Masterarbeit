//
//  Operator.h
//

#ifndef RuleBasedOptimizer_Operator_h
#define RuleBasedOptimizer_Operator_h

enum Operator
{
    JOIN,
    SCAN,
    SIZE_OF_ENUM
};

static const char* operatorname[SIZE_OF_ENUM] =
{
    "join",
    "scan"
};



#endif
