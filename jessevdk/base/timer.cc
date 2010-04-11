#include "timer.hh"

using namespace std;
using namespace jessevdk::base;

Timer::MarkPoint
Timer::Mark()
{
	d_last.tv_sec = 0;
	d_last.tv_usec = 0;

	gettimeofday(&d_last, NULL);
	return d_last;
}

double
Timer::Seconds(MarkPoint const &mark) const
{
	return static_cast<double>(mark.tv_sec) + static_cast<double>(mark.tv_usec) / 1000000.0;
}

double
Timer::Since() const
{
	return Since(d_last);
}

double
Timer::Since(MarkPoint const &mark) const
{
	MarkPoint now = {0,};
	gettimeofday(&now, NULL);

	return Seconds(now) - Seconds(mark);
}

Timer::Timer()
{
	Mark();
}
