#ifndef __MATH_OPERATORS_H__
#define __MATH_OPERATORS_H__

namespace math
{
	template <typename Base>
	struct Operators
	{
		typedef typename Base::type (*binary_operator)(typename Base::type a, typename Base::type b);
		typedef typename Base::type (*unary_operator)(typename Base::type a);

		static inline Base operate(Base const &o, unary_operator op)
		{
			Base ret;

			for (size_t i = 0; i < Base::size; ++i)
				ret.values[i] = (*op)(o[i]);
			
			return ret;
		}
		
		static inline Base &operate(Base &o, unary_operator op)
		{
			for (size_t i = 0; i < Base::size; ++i)
				o.values[i] = (*op)(o[i]);
			
			return o;
		}
		
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
		
		static inline typename Base::type floor(typename Base::type a)
		{
			return ::floor(a);
		}
		
		static inline typename Base::type ceil(typename Base::type a)
		{
			return ::ceil(a);
		}
		
		static inline typename Base::type clipMin(typename Base::type a, typename Base::type c)
		{
			return a < c ? c : a;
		}
		
		static inline typename Base::type clipMax(typename Base::type a, typename Base::type c)
		{
			return a > c ? c : a;
		}
	};
};

#endif /* __MATH_OPERATORS_H__ */
