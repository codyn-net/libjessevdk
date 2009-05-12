#ifndef __BASE_TIMER_H__
#define __BASE_TIMER_H__

#include <sys/time.h>
#include <time.h>

namespace base
{
	class Timer
	{
		public:
			typedef timeval Mark;

			/* Constructor/destructor */
			Timer();

			/* Public functions */
			Mark mark();

			double since() const;
			double since(Mark const &mark) const;
			double seconds(Mark const &mark) const;
		private:
			/* Private functions */
			Mark d_last;
	};
}

#endif /* __BASE_TIMER_H__ */
