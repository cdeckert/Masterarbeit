//
//  Stopwatch.h
//  RuleBasedOptimizer
//
//  Created by Christian Deckert on 15/04/15.
//  Copyright (c) 2015 Christian Deckert. All rights reserved.
//

#ifndef __RuleBasedOptimizer__Stopwatch__
#define __RuleBasedOptimizer__Stopwatch__

#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>

class Stopwatch
{
	typedef unsigned int u_int;
public:
	Stopwatch();
	void start();
	void stop();
	u_int getTime();
	
private:
	std::chrono::steady_clock::time_point _start;
	std::chrono::steady_clock::time_point _end;
};


#endif /* defined(__RuleBasedOptimizer__Stopwatch__) */
