#ifndef __OS_ENVIRONMENT_H__
#define __OS_ENVIRONMENT_H__

#include <string>
#include <vector>
#include <map>

namespace os
{
	class Environment
	{
		public:
			static bool variable(std::string const &name, std::string &value);
			static bool variable(std::string const &name);
			static std::vector<std::string> path(std::string const &name);
			
			static std::map<std::string, std::string> all();
			static std::vector<std::string> convert(std::map<std::string, std::string> const &environment);
		private:
			/* Private functions */
			Environment(); // NI
		
	};
}

#endif /* __OS_ENVIRONMENT_H__ */
