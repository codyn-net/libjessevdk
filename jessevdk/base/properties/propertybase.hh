#ifndef __JESSEVDK_BASE_PROPERTIES_PROPERTY_BASE_H__
#define __JESSEVDK_BASE_PROPERTIES_PROPERTY_BASE_H__

#include <string>
#include <iostream>

namespace jessevdk
{
namespace base
{
namespace properties
{
	class PropertyBase
	{
		public:
			virtual ~PropertyBase() {};
			virtual PropertyBase *Clone() const;
			virtual PropertyBase &operator=(std::string const &value);
			virtual bool Serializable() const;
			virtual operator std::string() const;
	};

	inline PropertyBase *
	PropertyBase::Clone() const
	{
		return new PropertyBase();
	}

	inline PropertyBase &
	PropertyBase::operator=(std::string const &value)
	{
		return *this;
	}

	inline bool
	PropertyBase::Serializable() const
	{
		return false;
	}

	inline PropertyBase::operator std::string() const
	{
		return "";
	}

	inline std::ostream &operator<<(std::ostream &ostr, PropertyBase const &property)
	{
		return ostr << std::string(property);
	}
}
}
}

#endif /* __JESSEVDK_BASE_PROPERTIES_PROPERTY_BASE_H__ */
