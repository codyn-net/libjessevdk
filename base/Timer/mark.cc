#include "timer.ih"

Timer::Mark Timer::mark() 
{
	d_last.tv_sec = 0;
	d_last.tv_usec = 0;

	gettimeofday(&d_last, NULL);
	return d_last;
}
