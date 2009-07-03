#ifndef __OS_ENVIRONMENT_H__
#define __OS_ENVIRONMENT_H__

#include <string>
#include <vector>

namespace os
{
	class Environment
	{
		public:
			static bool variable(std::string const &name, std::string &value);
			static bool variable(std::string const &name);
			static std::vector<std::string> path(std::string const &name);
			
			static std::vector<std::string> all();
		private:
			/* Private functions */
			Environment(); // NI
		
	};
}

#endif /* __OS_ENVIRONMENT_H__ */
