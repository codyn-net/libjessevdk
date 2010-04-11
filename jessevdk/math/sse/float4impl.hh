#ifndef __JESSEVDK_MATH_SSE_FLOAT4_IMPL_H__
#define __JESSEVDK_MATH_SSE_FLOAT4_IMPL_H__

#include <jessevdk/math/sse/implementation.hh>
#include <cmath>

namespace jessevdk
{
namespace math
{
namespace sse
{
	class Float4Impl : public Implementation
	{
		public:
			virtual float Sum(Vec<Vec4Data<float> > const &v)
			{
				return v.values[0] + v.values[1] + v.values[2] + v.values[3];
			}

			virtual float Index(Vec<Vec4Data<float> > const &v, size_t idx)
			{
				return *((float *)&v + idx);
			}

			virtual float &Index(Vec<Vec4Data<float> > &v, size_t idx)
			{
				return *((float *)&v + idx);
			}

			/* addition */
			virtual Vec<Vec4Data<float> > Add(Vec<Vec4Data<float> > const &v, float single)
			{
				return Operate(v, single, std::plus<float>());
			}

			virtual Vec<Vec4Data<float> > Add(Vec<Vec4Data<float> > const &v, Vec<Vec4Data<float> > const &other)
			{
				return Operate(v, other, std::plus<float>());
			}

			virtual Vec<Vec4Data<float> > &Add(Vec<Vec4Data<float> > &v, float single)
			{
				return Operate(v, single, std::plus<float>());
			}

			virtual Vec<Vec4Data<float> > &Add(Vec<Vec4Data<float> > &v, Vec<Vec4Data<float> > const &other)
			{
				return Operate(v, other, std::plus<float>());
			}

			/* substraction */
			virtual Vec<Vec4Data<float> > Substract(Vec<Vec4Data<float> > const &v, float single)
			{
				return Operate(v, single, std::minus<float>());
			}

			virtual Vec<Vec4Data<float> > Substract(Vec<Vec4Data<float> > const &v, Vec<Vec4Data<float> > const &other)
			{
				return Operate(v, other, std::minus<float>());
			}

			virtual Vec<Vec4Data<float> > &Substract(Vec<Vec4Data<float> > &v, float single)
			{
				return Operate(v, single, std::minus<float>());
			}

			virtual Vec<Vec4Data<float> > &Substract(Vec<Vec4Data<float> > &v, Vec<Vec4Data<float> > const &other)
			{
				return Operate(v, other, std::minus<float>());
			}

			/* multiplication */
			virtual Vec<Vec4Data<float> > Multiply(Vec<Vec4Data<float> > const &v, float single)
			{
				return Operate(v, single, std::multiplies<float>());
			}

			virtual Vec<Vec4Data<float> > Multiply(Vec<Vec4Data<float> > const &v, Vec<Vec4Data<float> > const &other)
			{
				return Operate(v, other, std::multiplies<float>());
			}

			virtual Vec<Vec4Data<float> > &Multiply(Vec<Vec4Data<float> > &v, float single)
			{
				return Operate(v, single, std::multiplies<float>());
			}

			virtual Vec<Vec4Data<float> > &Multiply(Vec<Vec4Data<float> > &v, Vec<Vec4Data<float> > const &other)
			{
				return Operate(v, other, std::multiplies<float>());
			}

			/* division */
			virtual Vec<Vec4Data<float> > Divide(Vec<Vec4Data<float> > const &v, float single)
			{
				return Operate(v, single, std::divides<float>());
			}

			virtual Vec<Vec4Data<float> > Divide(Vec<Vec4Data<float> > const &v, Vec<Vec4Data<float> > const &other)
			{
				return Operate(v, other, std::divides<float>());
			}

			virtual Vec<Vec4Data<float> > &Divide(Vec<Vec4Data<float> > &v, float single)
			{
				return Operate(v, single, std::divides<float>());
			}

			virtual Vec<Vec4Data<float> > &Divide(Vec<Vec4Data<float> > &v, Vec<Vec4Data<float> > const &other)
			{
				return Operate(v, other, std::divides<float>());
			}

			virtual float Length(Vec<Vec4Data<float> > const &v)
			{
				return Sqrt(Dot(v, v));
			}

			virtual Vec<Vec4Data<float> > Normalize(Vec<Vec4Data<float> > const &v)
			{
				return Divide(v, Length(v));
			}

			virtual Vec<Vec4Data<float> > &Normalize(Vec<Vec4Data<float> > &v)
			{

				return Divide(v, Length(v));
			}

			virtual Vec<Vec4Data<float> > Invert(Vec<Vec4Data<float> > const &v)
			{
				return Multiply(v, -1);
			}

			virtual Vec<Vec4Data<float> > &Invert(Vec<Vec4Data<float> > &v)
			{
				return Multiply(v, -1);
			}

			virtual float Dot(Vec<Vec4Data<float> > const &v, Vec<Vec4Data<float> > const &other)
			{
				return v.values[0] * other.values[0] +
					   v.values[1] * other.values[1] +
					   v.values[2] * other.values[2] +
					   v.values[3] * other.values[3];
			}
		private:
			template <typename Operator>
			inline Vec<Vec4Data<float> >Operate(Vec<Vec4Data<float> > const &v, Vec<Vec4Data<float> > const &other, Operator op) const
			{
				Vec<Vec4Data<float> > copy;

				for (size_t i = 0; i < 4; ++i)
					copy.values[i] = op(v.values[i], other.values[i]);

				return copy;
			}

			template <typename Operator>
			inline Vec<Vec4Data<float> > Operate(Vec<Vec4Data<float> > const &v, float single, Operator op)
			{
				Vec<Vec4Data<float> > copy;

				for (size_t i = 0; i < 4; ++i)
					copy.values[i] = op(v.values[i], single);

				return copy;
			}

			template <typename Operator>
			inline Vec<Vec4Data<float> > &Operate(Vec<Vec4Data<float> > &v, float single, Operator op)
			{
				for (size_t i = 0; i < 4; ++i)
					v.values[i] = op(v.values[i], single);

				return v;
			}

			template <typename Operator>
			inline Vec<Vec4Data<float> > &Operate(Vec<Vec4Data<float> > &v, Vec<Vec4Data<float> > const &other, Operator op)
			{
				for (size_t i = 0; i < 4; ++i)
					v.values[i] = op(v.values[i], other.values[i]);

				return v;
			}
	};
}
}
}

#endif /* __JESSEVDK_MATH_SSE_FLOAT4_IMPL_H__ */

