//
//  Stopwatch.cpp
//

#include "Stopwatch.h"


Stopwatch::Stopwatch()
{
	start();
	stop();
};

void Stopwatch::start()
{
	_start = std::chrono::steady_clock::now();
};

void Stopwatch::stop()
{
	_end = std::chrono::steady_clock::now();
};


u_int Stopwatch::getDuration()
{
	return std::chrono::duration_cast<std::chrono::microseconds>(_end - _start).count();
};