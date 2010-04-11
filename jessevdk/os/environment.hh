#ifndef __JESSEVDK_OS_ENVIRONMENT_H__
#define __JESSEVDK_OS_ENVIRONMENT_H__

#include <string>
#include <vector>
#include <map>

namespace jessevdk
{
namespace os
{
	class Environment
	{
		public:
			static bool Variable(std::string const &name, std::string &value);
			static bool Variable(std::string const &name);
			static std::vector<std::string> Path(std::string const &name);

			static std::map<std::string, std::string> All();
			static std::vector<std::string> Convert(std::map<std::string, std::string> const &environment);
		private:
			/* Private functions */
			Environment(); // NI

	};
}
}

#endif /* __JESSEVDK_OS_ENVIRONMENT_H__ */
