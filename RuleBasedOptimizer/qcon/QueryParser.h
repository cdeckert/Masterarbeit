//
//  QueryParser.h
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 2/17/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#ifndef __RuleBasedOptimizer__QueryParser__
#define __RuleBasedOptimizer__QueryParser__

#include <stdio.h>
#include "Types.h"
#include "Scanner.h"



class QueryParser {
    
public:
    QueryParser(const std::string& aFilename) : _scanner(aFilename){};
    ~QueryParser()
    {
        //delete _scanner;
    };
private:
    const Scanner _scanner;
};


#endif /* defined(__RuleBasedOptimizer__QueryParser__) */
