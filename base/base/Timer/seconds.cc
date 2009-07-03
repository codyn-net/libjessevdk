#include "timer.ih"

double Timer::seconds(Mark const &mark) const
{
	return static_cast<double>(mark.tv_sec) + static_cast<double>(mark.tv_usec) / 1000000.0;
}
