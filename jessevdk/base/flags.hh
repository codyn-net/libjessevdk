#ifndef __JESSEVDK_BASE_FLAGS__
#define __JESSEVDK_BASE_FLAGS__

#include <jessevdk/base/enum.hh>

namespace jessevdk
{
namespace base
{
	template <typename Type>
	class Flags : public Enum<Type>
	{
		public:
			/* Constructor/destructor */
			Flags();
			Flags(typename Enum<Type>::Value const &value);
			Flags(int value);

			/* Public functions */
			Flags<Type> &operator<<(typename Enum<Type>::Value const &value);
			Flags<Type> &Add(typename Enum<Type>::Value const &value);

			Flags<Type> &operator>>(typename Enum<Type>::Value const &value);
			Flags<Type> &Remove(typename Enum<Type>::Value const &value);

			Flags<Type> operator&(Flags<Type> const &other) const;
			Flags<Type> operator&(typename Enum<Type>::Value const &other) const;
			Flags<Type> operator&(int value) const;

			Flags<Type> &operator&=(Flags<Type> const &other);
			Flags<Type> &operator&=(typename Enum<Type>::Value const &other);
			Flags<Type> &operator&=(int value);

			Flags<Type> operator|(Flags<Type> const &other) const;
			Flags<Type> operator|(typename Enum<Type>::Value const &other) const;
			Flags<Type> operator|(int value) const;

			Flags<Type> &operator|=(Flags<Type> const &other);
			Flags<Type> &operator|=(typename Enum<Type>::Value const &other);
			Flags<Type> &operator|=(int value);
		private:
			/* Private functions */

	};

	template <typename Type>
	inline Flags<Type>::Flags()
	:
		Enum<Type>()
	{
	}

	template <typename Type>
	inline Flags<Type>::Flags(typename Enum<Type>::Value const &value)
	:
		Enum<Type>(value)
	{
	}

	template <typename Type>
	inline Flags<Type>::Flags(int value)
	:
		Enum<Type>(value)
	{
	}

	template <typename Type>
	inline Flags<Type> &Flags<Type>::operator<<(typename Enum<Type>::Value const &value)
	{
		Add(value);
		return *this;
	}

	template <typename Type>
	inline Flags<Type> &Flags<Type>::Add(typename Enum<Type>::Value const &value)
	{
		Set(this->Get() | value);
		return *this;
	}

	template <typename Type>
	inline Flags<Type> &Flags<Type>::operator>>(typename Enum<Type>::Value const &value)
	{
		Remove(value);
		return *this;
	}

	template <typename Type>
	inline Flags<Type> &Flags<Type>::Remove(typename Enum<Type>::Value const &value)
	{
		Set(this->Get() & ~value);
		return *this;
	}

	template <typename Type>
	inline Flags<Type> Flags<Type>::operator&(Flags<Type> const &other) const
	{
		return Flags<Type>(this->Get() & other.Get());
	}

	template <typename Type>
	inline Flags<Type> Flags<Type>::operator&(typename Enum<Type>::Value const &other) const
	{
		return Flags<Type>(static_cast<typename Enum<Type>::Value>(this->Get() & other));
	}

	template <typename Type>
	inline Flags<Type> Flags<Type>::operator&(int value) const
	{
		return Flags<Type>(static_cast<typename Enum<Type>::Value>(this->Get() & value));
	}

	template <typename Type>
	inline Flags<Type> Flags<Type>::operator|(Flags<Type> const &other) const
	{
		return Flags<Type>(this->Get() & other.Get());
	}

	template <typename Type>
	inline Flags<Type> Flags<Type>::operator|(typename Enum<Type>::Value const &other) const
	{
		return Flags<Type>(static_cast<typename Enum<Type>::Value>(this->Get() & other));
	}

	template <typename Type>
	inline Flags<Type> Flags<Type>::operator|(int value) const
	{
		return Flags<Type>(static_cast<typename Enum<Type>::Value>(this->Get() & value));
	}

	template <typename Type>
	inline Flags<Type> &Flags<Type>::operator&=(Flags<Type> const &other)
	{
		Set(this->Get() & other.Get());
		return *this;
	}

	template <typename Type>
	inline Flags<Type> &Flags<Type>::operator&=(typename Enum<Type>::Value const &other)
	{
		Set(static_cast<typename Enum<Type>::Value>(this->Get() & other));
		return *this;
	}

	template <typename Type>
	inline Flags<Type> &Flags<Type>::operator&=(int value)
	{
		Set(Flags<Type>(static_cast<typename Enum<Type>::Value>(this->Get() & value)));
		return *this;
	}

	template <typename Type>
	inline Flags<Type> &Flags<Type>::operator|=(Flags<Type> const &other)
	{
		Set(this->Get() & other.Get());
		return *this;
	}

	template <typename Type>
	inline Flags<Type> &Flags<Type>::operator|=(typename Enum<Type>::Value const &other)
	{
		Set(static_cast<typename Enum<Type>::Value>(this->Get() & other));
		return *this;
	}

	template <typename Type>
	inline Flags<Type> &Flags<Type>::operator|=(int value)
	{
		Set(static_cast<typename Enum<Type>::Value>(this->Get() & value));
		return *this;
	}
}
}

#endif /* __JESSEVDK_BASE_FLAGS__ */
