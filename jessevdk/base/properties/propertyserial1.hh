#ifndef __JESSEVDK_BASE_PROPERTIES_PROPERTY_SERIAL1_H__
#define __JESSEVDK_BASE_PROPERTIES_PROPERTY_SERIAL1_H__

#include <jessevdk/base/properties/property1.hh>
#include <sstream>
#include <iostream>
#include <jessevdk/base/string.hh>

namespace jessevdk
{
namespace base
{
namespace properties
{
	template <typename Type>
	class PropertySerial : public Property<Type>
	{
		public:
			PropertySerial(std::string const &name, Type &storage);

			virtual PropertySerial<Type> *Clone() const;
			PropertySerial<Type> &operator=(std::string const &value);
			virtual bool Serializable() const;

			virtual operator std::string() const;
	};

	namespace
	{
		template <typename T>
		struct Implementation
		{
			static bool Deserialize(std::string const &s, T &val)
			{
				std::istringstream istr(s);

				return istr >> val;
			}

			static bool Serialize(T const &v, std::string &val)
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
		struct Implementation<bool>
		{
			static bool Deserialize(std::string const &s, bool &val)
			{
				val = (s == "yes" || s == "1" || s == "true" || s == "YES" || s == "TRUE");
				return true;
			}

			static bool Serialize(bool const &v, std::string &val)
			{
				val = v ? "yes" : "no";
				return true;
			}
		};

		template <typename T>
		struct Implementation<std::vector<T> >
		{
			static bool Deserialize(std::string const &s, std::vector<T> &val)
			{
				std::vector<std::string> parts = jessevdk::base::String(s).Split(",");
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

			static bool Serialize(std::vector<T> const &v, std::string &val)
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
	inline PropertySerial<Type> *PropertySerial<Type>::Clone() const
	{
		return new PropertySerial<Type>(*this);
	}

	template <typename Type>
	inline bool PropertySerial<Type>::Serializable() const
	{
		return true;
	}

	template <typename Type>
	inline PropertySerial<Type> &PropertySerial<Type>::operator=(std::string const &value)
	{
		Type val;

		if (Implementation<Type>::Deserialize(value, val))
		{
			Set(val);
		}

		return *this;
	}

	template <typename Type>
	inline PropertySerial<Type>::operator std::string() const
	{
		std::string val;

		if (Implementation<Type>::Serialize(Property<Type>::operator Type const &(), val))
		{
			return val;
		}
		else
		{
			return Property<Type>::operator std::string();
		}
	}
}
}
}

#endif /* __JESSEVDK_BASE_PROPERTIES_PROPERTY_SERIAL1_H__ */
