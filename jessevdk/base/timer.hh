#ifndef __JESSEVDK_BASE_TIMER_H__
#define __JESSEVDK_BASE_TIMER_H__

#include <sys/time.h>
#include <time.h>

namespace jessevdk
{
namespace base
{
	class Timer
	{
		public:
			typedef timeval MarkPoint;

			/* Constructor/destructor */
			Timer();

			/* Public functions */
			MarkPoint Mark();

			double Since() const;
			double Since(MarkPoint const &mark) const;
			double Seconds(MarkPoint const &mark) const;
		private:
			/* Private functions */
			MarkPoint d_last;
	};
}
}

#endif /* __JESSEVDK_BASE_TIMER_H__ */
