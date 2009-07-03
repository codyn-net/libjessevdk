#include "timer.ih"
#include <iostream>

double Timer::since(Mark const &mark) const
{
	Mark now = {0,};
	gettimeofday(&now, NULL);
	
	return seconds(now) - seconds(mark);
}
