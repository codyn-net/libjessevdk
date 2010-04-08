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
			void Add(typename Enum<Type>::Value const &value);

			Flags<Type> &operator>>(typename Enum<Type>::Value const &value);
			void Remove(typename Enum<Type>::Value const &value);

			Flags<Type> operator&(Flags<Type> const &other) const;
			Flags<Type> operator&(typename Enum<Type>::Value const &other) const;
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
	inline void Flags<Type>::Add(typename Enum<Type>::Value const &value)
	{
		*this = this->Get() | value;
	}

	template <typename Type>
	inline Flags<Type> &Flags<Type>::operator>>(typename Enum<Type>::Value const &value)
	{
		Remove(value);
		return *this;
	}

	template <typename Type>
	inline void Flags<Type>::Remove(typename Enum<Type>::Value const &value)
	{
		*this = this->Get() & ~value;
	}

	template <typename Type>
	inline Flags<Type> Flags<Type>::operator&(Flags<Type> const &other) const
	{
		return Flags<Type>(this->Get() & other.Get());
	}

	template <typename Type>
	Flags<Type> Flags<Type>::operator&(typename Enum<Type>::Value const &other) const
	{
		return Flags<Type>(static_cast<typename Enum<Type>::Value>(this->Get() & other));
	}
}
}

#endif /* __JESSEVDK_BASE_FLAGS__ */
