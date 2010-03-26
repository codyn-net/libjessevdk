#ifndef __JESSEVDK_OS_TERMINATOR_H__
#define __JESSEVDK_OS_TERMINATOR_H__

#include <glibmm.h>
#include <jessevdk/base/object.hh>

namespace jessevdk
{
namespace os
{
	class Terminator : public base::Object
	{
		struct Data : public base::Object::PrivateData
		{
			struct Stage
			{
				enum Values
				{
					None = 0,
					Terminate,
					Kill
				};
			};

			GPid d_pid;
			sigc::connection d_timeout;
			sigc::connection d_watch;
			Stage::Values d_stage;
			bool d_recursive;

			base::signals::Signal<int> OnTerminated;

			bool OnTimeout();
			void OnChildKilled(GPid pid, int ret);

			void Kill(int sig);

			~Data();
		};

		Data *d_data;

		public:
			Terminator();

			int Terminate(GPid pid, bool recursive = false, bool block = true);

			jessevdk::base::signals::Signal<int> &OnTerminated();
		private:
	};
}

}

#endif /* __JESSEVDK_OS_TERMINATOR_H__ */
