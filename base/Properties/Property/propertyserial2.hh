#ifndef __BASE_PROPERTY_SERIAL2_H__
#define __BASE_PROPERTY_SERIAL2_H__

#include "property1.hh"
#include <sstream>
#include <iostream>

namespace base
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

#endif /* __BASE_PROPERTY_SERIAL2_H__ */
