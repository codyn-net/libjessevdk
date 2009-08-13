#ifndef __BASE_CONFIG_H__
#define __BASE_CONFIG_H__

#include <base/Object/object.hh>
#include <base/Properties/properties.hh>

namespace base
{
	class Config : public Object, public Properties
	{
		public:
			Config();

			void read(std::string const &filename);
	};
}

#endif /* __BASE_CONFIG_H__ */
