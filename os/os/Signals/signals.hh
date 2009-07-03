#ifndef __OS_SIGNALS_H__
#define __OS_SIGNALS_H__

#include <signal.h>
#include <base/Signals/Signal/signal.hh>

namespace os
{
	class Signals
	{
		static volatile sig_atomic_t s_stopping;
		static volatile sig_atomic_t s_fatalError;
		
		public:
			static base::signals::Signal<> onInterrupt;

			/* Public functions */
			static void install();
			static void uninstall();
			
			static bool stopping();
			static void setStopping(bool val);
			
			static bool fatalError();
			static void setFatalError(bool val);
			
			static size_t interrupted();
		private:
			/* Private functions */
			Signals(); // NI
	};
	
	inline bool Signals::stopping()
	{
		return s_stopping;
	}
	
	inline void Signals::setStopping(bool val)
	{
		s_stopping = val;
	}
	
	inline bool Signals::fatalError()
	{
		return s_fatalError;
	}
	
	inline void Signals::setFatalError(bool val)
	{
		s_fatalError = val;
	}
}

#endif /* __OS_SIGNALS_H__ */
