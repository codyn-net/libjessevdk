#ifndef __MATH_OPERATORS_H__
#define __MATH_OPERATORS_H__

namespace math
{
	template <typename Base>
	struct Operators
	{
		typedef typename Base::type (*binary_operator)(typename Base::type a, typename Base::type b);

		static inline Base operate(Base const &o, Base const &other, binary_operator op)
		{
			Base copy;

			for (size_t i = 0; i < Base::size; ++i)
				copy.values[i] = (*op)(o[i], other[i]);
			
			return copy;
		}

		static inline Base operate(Base const &o, typename Base::type single, binary_operator op)
		{
			Base copy;
			
			for (size_t i = 0; i < Base::size; ++i)
				copy.values[i] = (*op)(o[i], single);
			
			return copy;
		}

		static inline Base &operate(Base &o, typename Base::type single, binary_operator op)
		{
			for (size_t i = 0; i < Base::size; ++i)
				o.values[i] = (*op)(o[i], single);
			
			return o;
		}

		static inline Base &operate(Base &o, Base const &other, binary_operator op)
		{			
			for (size_t i = 0; i < Base::size; ++i)
				o.values[i] = (*op)(o[i], other[i]);
			
			return o;
		}
		
		/* binary operators */
		static inline typename Base::type multiplier(typename Base::type a, typename Base::type b)
		{
			return a * b;
		}
		
		static inline typename Base::type divider(typename Base::type a, typename Base::type b)
		{
			return a / b;
		}
		
		static inline typename Base::type modulator(typename Base::type a, typename Base::type b)
		{
			return a % b;
		}
		
		static inline typename Base::type adder(typename Base::type a, typename Base::type b)
		{
			return a + b;
		}
		
		static inline typename Base::type substractor(typename Base::type a, typename Base::type b)
		{
			return a - b;
		}
	};
};

#endif /* __MATH_OPERATORS_H__ */
