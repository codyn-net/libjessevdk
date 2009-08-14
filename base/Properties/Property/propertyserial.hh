#ifndef __BASE_PROPERTY_SERIAL_H__
#define __BASE_PROPERTY_SERIAL_H__

#include <base/Properties/Property/property1.hh>
#include <sstream>
#include <iostream>
#include <base/String/string.hh>

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

	namespace
	{
		template <typename T>
		struct implementation
		{
			static bool deserialize(std::string const &s, T &val)
			{
				std::istringstream istr(s);
				
				return istr >> val;
			}
			
			static bool serialize(T const &v, std::string &val)
			{
				std::ostringstream ostr;
				
				if (ostr << v)
				{
					val = ostr.str();
					return true;
				}
				
				return false;
			}
		};
		
		template <>
		struct implementation<bool>
		{
			static bool deserialize(std::string const &s, bool &val)
			{
				val = (s == "yes" || s == "1" || s == "true" || s == "YES" || s == "TRUE");
				return true;
			}
			
			static bool serialize(bool const &v, std::string &val)
			{
				val = v ? "yes" : "no";
				return true;
			}
		};
		
		template <typename T>
		struct implementation<std::vector<T> >
		{
			static bool deserialize(std::string const &s, std::vector<T> &val)
			{
				std::vector<std::string> parts = base::String(s).split(",");
				std::vector<std::string>::iterator iter;
				
				for (iter = parts.begin(); iter != parts.end(); ++iter)
				{
					T v;
					std::istringstream istr(*iter);
					
					if (!(istr >> v))
						return false;

					val.push_back(v);
				}

				return true;
			}
			
			static bool serialize(std::vector<T> const &v, std::string &val)
			{
				typename std::vector<T>::const_iterator iter;
				std::ostringstream ostr;
				
				for (iter = v.begin(); iter != v.end(); ++iter)
				{
					if (!(ostr << *iter))
						return false;
					
					if (iter != v.end())
						ostr << ",";
				}
				
				val = ostr.str();
				return true;
			}
		};
	}

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
		Type val;
		
		if (implementation<Type>::deserialize(value, val))
			set(val);
		
		return *this;
	}
	
	template <typename Type>
	inline PropertySerial<Type>::operator std::string() const
	{
		std::string val;
		
		if (implementation<Type>::serialize(Property<Type>::operator Type const &(), val))
			return val;
		else
			return Property<Type>::operator std::string();
	}
}

#endif /* __BASE_PROPERTY_SERIAL_H__ */
