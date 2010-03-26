#ifndef __JESSEVDK_OS_PROCESSES_H__
#define __JESSEVDK_OS_PROCESSES_H__

#include <vector>
#include <map>
#include <glibmm.h>

namespace jessevdk
{
namespace os
{
	class Processes
	{
		public:
			static pid_t Parent(GPid pid);
			static std::vector<GPid> Children(GPid pid, bool recurse = false);
		private:
			static std::vector<GPid> Collect(std::map<GPid, std::vector<GPid> > const &mapping,
			                                 GPid                                      parent,
			                                 bool                                      recurse);
	};
}
}

#endif /* __JESSEVDK_OS_PROCESSES_H__ */

