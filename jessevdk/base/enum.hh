#ifndef __JESSEVDK_BASE_ENUM__
#define __JESSEVDK_BASE_ENUM__

#include <string>
#include <jessevdk/base/exceptions/badvalue.hh>
#include <jessevdk/base/signals/signal.hh>

namespace jessevdk
{
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
			Value const &Get() const;

			std::string const &Name() const;
			operator std::string const &() const;

			Enum<Type> &operator=(int value);
			Enum<Type> &operator=(Value value);

			signals::Signal<Value> OnChanged;
		protected:
			void Set(Value newValue);
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
		return Get();
	}

	template <typename Type>
	inline typename Enum<Type>::Value const &Enum<Type>::Get() const
	{
		return d_value;
	}

	template <typename Type>
	inline std::string const &Enum<Type>::Name() const
	{
		return Type::Names[d_value];
	}

	template <typename Type>
	inline Enum<Type>::operator std::string const &() const
	{
		return Name();
	}

	template <typename Type>
	inline Enum<Type> &
	Enum<Type>::operator=(int value)
	{
		Set(static_cast<Value>(value));
		return *this;
	}

	template <typename Type>
	inline Enum<Type> &
	Enum<Type>::operator=(Value value)
	{
		Set(value);
		return *this;
	}

	template <typename Type>
	inline void
	Enum<Type>::Set(Value value)
	{
		if (d_value == value)
		{
			return;
		}

		Value old = d_value;

		d_value = value;
		OnChanged(old);
	}

	template <typename Type>
	inline std::ostream &operator<<(std::ostream &ostr, Enum<Type> const &en)
	{
		return ostr << en.Name();
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

		throw exceptions::BadValue("Bad enum value `" + name + "'");
	}
}
}

#endif /* __JESSEVDK_BASE_ENUM__ */
