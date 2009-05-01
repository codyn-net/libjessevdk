#ifndef __BASE_PROPERTY_SERIAL_H__
#define __BASE_PROPERTY_SERIAL_H__

#include "property1.hh"
#include <sstream>
#include <iostream>

namespace base
{
	template <typename Type>
	class PropertySerial : public Property<Type>
	{
		public:
			PropertySerial(std::string const &name, Type &storage);
			
			virtual PropertySerial<Type> *clone() const;
			PropertySerial<Type> &operator=(std::string const &value);
			virtual bool serializable() const;
			
			virtual operator std::string() const;
	};
	
	template <typename Type>
	inline PropertySerial<Type>::PropertySerial(std::string const &name, Type &storage)
	:
		Property<Type>(name, storage)
	{
	}
	
	template <typename Type>
	inline PropertySerial<Type> *PropertySerial<Type>::clone() const
	{
		return new PropertySerial<Type>(*this);
	}
	
	template <typename Type>
	inline bool PropertySerial<Type>::serializable() const
	{
		return true;
	}
	
	template <typename Type>
	inline PropertySerial<Type> &PropertySerial<Type>::operator=(std::string const &value)
	{
		std::istringstream istr(value);
		
		Type val;
		
		if (istr >> val)		
			set(val);
		
		return *this;
	}
	
	template <typename Type>
	inline PropertySerial<Type>::operator std::string() const
	{
		std::ostringstream ostr;
		
		if (ostr << (Property<Type>::operator Type const &()))
			return ostr.str();
		else
			return Property<Type>::operator std::string();
	}
}

#endif /* __BASE_PROPERTY_SERIAL_H__ */
