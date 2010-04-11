#ifndef __JESSEVDK_OS_SIGNALS_H__
#define __JESSEVDK_OS_SIGNALS_H__

#include <signal.h>
#include <jessevdk/base/signals/signal.hh>

namespace jessevdk
{
namespace os
{
	class Signals
	{
		static volatile sig_atomic_t s_stopping;
		static volatile sig_atomic_t s_fatalError;

		public:
			static base::signals::Signal<> OnInterrupt;

			/* Public functions */
			static void Install();
			static void Uninstall();

			static bool Stopping();
			static void SetStopping(bool val);

			static bool FatalError();
			static void SetFatalError(bool val);

			static size_t Interrupted();
		private:
			/* Private functions */
			Signals(); // NI
	};

	inline bool Signals::Stopping()
	{
		return s_stopping;
	}

	inline void Signals::SetStopping(bool val)
	{
		s_stopping = val;
	}

	inline bool Signals::FatalError()
	{
		return s_fatalError;
	}

	inline void Signals::SetFatalError(bool val)
	{
		s_fatalError = val;
	}
}
}

#endif /* __JESSEVDK_OS_SIGNALS_H__ */
