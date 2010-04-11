#ifndef __JESSEVDK_BASE_PROPERTIES_PROPERTY_SERIAL2_H__
#define __JESSEVDK_BASE_PROPERTIES_PROPERTY_SERIAL2_H__

#include <jessevdk/base/properties/propertyserial1.hh>
#include <sstream>
#include <iostream>

namespace jessevdk
{
namespace base
{
namespace properties
{
	template <>
	class PropertySerial<std::string> : public Property<std::string>
	{
		public:
			PropertySerial(std::string const &name, std::string &storage);
	};

	inline PropertySerial<std::string>::PropertySerial(std::string const &name, std::string &storage)
	:
		Property<std::string>(name, storage)
	{
	}
}
}
}

#endif /* __JESSEVDK_BASE_PROPERTIES_PROPERTY_SERIAL2_H__ */
