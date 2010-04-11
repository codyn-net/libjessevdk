#ifndef __JESSEVDK_BASE_CONFIG_H__
#define __JESSEVDK_BASE_CONFIG_H__

#include <jessevdk/base/object.hh>
#include <jessevdk/base/properties/properties.hh>

namespace jessevdk
{
namespace base
{
	class Config : public Object, public properties::Properties
	{
		public:
			Config();

			void Read(std::string const &filename);
	};
}
}

#endif /* __JESSEVDK_BASE_CONFIG_H__ */
