#ifndef __BASE_ENUM__
#define __BASE_ENUM__

#include <string>
#include <base/Exceptions/exceptions.hh>

namespace base
{
	template <typename Type>
	class Enum
	{
		public:
			typedef typename Type::Values Value;

			/* Constructor/destructor */
			Enum();
			Enum(Value const &value);
			Enum(int value);

			/* Public functions */
			operator Value() const;
			Value const &value() const;

			std::string const &name() const;
			operator std::string const &() const;
		private:
			/* Private functions */
			Value d_value;
	};
	
	template <typename Type>
	inline Enum<Type>::Enum()
	:
		d_value(static_cast<Value>(0))
	{
	}
	
	template <typename Type>
	inline Enum<Type>::Enum(Enum<Type>::Value const &value)
	:
		d_value(value)
	{
	}
	
	template <typename Type>
	inline Enum<Type>::Enum(int value)
	:
		d_value(static_cast<Value>(value))
	{
	}
	
	template <typename Type>
	inline Enum<Type>::operator typename Enum<Type>::Value() const
	{
		return value();
	}
	
	template <typename Type>
	inline typename Enum<Type>::Value const &Enum<Type>::value() const
	{
		return d_value;
	}
	
	template <typename Type>
	inline std::string const &Enum<Type>::name() const
	{
		return Type::names[d_value];
	}
	
	template <typename Type>
	inline Enum<Type>::operator std::string const &() const
	{
		return name();
	}
	
	template <typename Type>
	inline std::ostream &operator<<(std::ostream &ostr, Enum<Type> const &en)
	{
		return ostr << en.name();
	}
	
	template <typename Type>
	inline std::istream &operator>>(std::istream &istr, Enum<Type> &en)
	{
		std::string name;
		istr >> name;
		
		for (size_t i = 0; i < sizeof(Type::names) / sizeof(Type::names[0]); ++i)
		{
			if (Type::names[i] == name)
			{
				en = i;
				return istr;
			}
		}
		
		throw exceptions::bad_value("Bad enum value `" + name + "'");
	}
}

#endif /* __BASE_ENUM__ */
