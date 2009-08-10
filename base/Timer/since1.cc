#include "timer.ih"

double Timer::since() const
{
	return since(d_last);
}
