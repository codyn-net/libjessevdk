#ifndef __JESSEVDK_MATH_OPERATORS_H__
#define __JESSEVDK_MATH_OPERATORS_H__

namespace jessevdk
{
namespace math
{
	template <typename Base>
	struct Operators
	{
		typedef typename Base::type (*binary_operator)(typename Base::type a, typename Base::type b);
		typedef typename Base::type (*unary_operator)(typename Base::type a);

		static inline Base Operate(Base const &o, unary_operator op)
		{
			Base ret;

			for (size_t i = 0; i < Base::size; ++i)
				ret.values[i] = (*op)(o[i]);

			return ret;
		}

		static inline Base &Operate(Base &o, unary_operator op)
		{
			for (size_t i = 0; i < Base::size; ++i)
				o.values[i] = (*op)(o[i]);

			return o;
		}

		static inline Base Operate(Base const &o, Base const &other, binary_operator op)
		{
			Base copy;

			for (size_t i = 0; i < Base::size; ++i)
				copy.values[i] = (*op)(o[i], other[i]);

			return copy;
		}

		static inline Base Operate(Base const &o, typename Base::type single, binary_operator op)
		{
			Base copy;

			for (size_t i = 0; i < Base::size; ++i)
				copy.values[i] = (*op)(o[i], single);

			return copy;
		}

		static inline Base &Operate(Base &o, typename Base::type single, binary_operator op)
		{
			for (size_t i = 0; i < Base::size; ++i)
				o.values[i] = (*op)(o[i], single);

			return o;
		}

		static inline Base &Operate(Base &o, Base const &other, binary_operator op)
		{
			for (size_t i = 0; i < Base::size; ++i)
				o.values[i] = (*op)(o[i], other[i]);

			return o;
		}

		/* binary operators */
		static inline typename Base::type Multiplier(typename Base::type a, typename Base::type b)
		{
			return a * b;
		}

		static inline typename Base::type Divider(typename Base::type a, typename Base::type b)
		{
			return a / b;
		}

		static inline typename Base::type Modulator(typename Base::type a, typename Base::type b)
		{
			return a % b;
		}

		static inline typename Base::type Adder(typename Base::type a, typename Base::type b)
		{
			return a + b;
		}

		static inline typename Base::type Substractor(typename Base::type a, typename Base::type b)
		{
			return a - b;
		}

		static inline typename Base::type Floor(typename Base::type a)
		{
			return ::floor(a);
		}

		static inline typename Base::type Ceil(typename Base::type a)
		{
			return ::ceil(a);
		}

		static inline typename Base::type ClipMin(typename Base::type a, typename Base::type c)
		{
			return a < c ? c : a;
		}

		static inline typename Base::type ClipMax(typename Base::type a, typename Base::type c)
		{
			return a > c ? c : a;
		}

		static inline typename Base::type Abs(typename Base::type a)
		{
			return a < 0 ? -a : a;
		}
	};
}
}

#endif /* __JESSEVDK_MATH_OPERATORS_H__ */
