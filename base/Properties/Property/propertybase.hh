#ifndef __BASE_PROPERTY_BASE_H__
#define __BASE_PROPERTY_BASE_H__

#include <string>
#include <iostream>

namespace base
{
	class PropertyBase
	{
		public:
			virtual ~PropertyBase() {};
			virtual PropertyBase *clone() const;
			virtual PropertyBase &operator=(std::string const &value);
			virtual bool serializable() const;
			virtual operator std::string() const;
	};
	
	inline PropertyBase *PropertyBase::clone() const
	{
		return new PropertyBase();
	}
	
	inline PropertyBase &PropertyBase::operator=(std::string const &value)
	{
		std::cout << "Calling = on property base" << std::endl;
		return *this;
	}
	
	inline bool PropertyBase::serializable() const
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

#endif /* __BASE_PROPERTY_BASE_H__ */
