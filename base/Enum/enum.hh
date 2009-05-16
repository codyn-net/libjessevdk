#ifndef __BASE_ENUM__
#define __BASE_ENUM__

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
}

#endif /* __BASE_ENUM__ */
