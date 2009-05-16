#ifndef __BASE_FLAGS__
#define __BASE_FLAGS__

#include <base/Enum/enum.hh>

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
			void add(typename Enum<Type>::Value const &value);
			
			Flags<Type> &operator>>(typename Enum<Type>::Value const &value);
			void remove(typename Enum<Type>::Value const &value);

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
		add(value);
		return *this;
	}
	
	template <typename Type>
	inline void Flags<Type>::add(typename Enum<Type>::Value const &value)
	{
		*this = this->value() | value;
	}
	
	template <typename Type>
	inline Flags<Type> &Flags<Type>::operator>>(typename Enum<Type>::Value const &value)
	{
		remove(value);
		return *this;
	}
	
	template <typename Type>
	inline void Flags<Type>::remove(typename Enum<Type>::Value const &value)
	{
		*this = this->value() & ~value;
	}
	
	template <typename Type>
	inline Flags<Type> Flags<Type>::operator&(Flags<Type> const &other) const
	{
		return Flags<Type>(this->value() & other.value());
	}
	
	template <typename Type>
	Flags<Type> Flags<Type>::operator&(typename Enum<Type>::Value const &other) const
	{
		return Flags<Type>(static_cast<typename Enum<Type>::Value>(this->value() & other));
	}
}

#endif /* __BASE_FLAGS__ */
