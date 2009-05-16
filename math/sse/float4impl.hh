#ifndef __MATH_SSE_FLOAT4_IMPL_H__
#define __MATH_SSE_FLOAT4_IMPL_H__

#include <math/sse/implementation.hh>
#include <cmath>

namespace math
{
namespace sse
{
	class Float4Impl : public Implementation
	{
		public:
			virtual float sum(Vec<Vec4Data<float> > const &v)
			{
				return v.values[0] + v.values[1] + v.values[2] + v.values[3];
			}

			virtual float index(Vec<Vec4Data<float> > const &v, size_t idx)
			{
				return *((float *)&v + idx);
			}
			
			virtual float &index(Vec<Vec4Data<float> > &v, size_t idx)
			{
				return *((float *)&v + idx);
			}
			
			/* addition */
			virtual Vec<Vec4Data<float> > add(Vec<Vec4Data<float> > const &v, float single) 
			{
				return operate(v, single, std::plus<float>());
			}
			
			virtual Vec<Vec4Data<float> > add(Vec<Vec4Data<float> > const &v, Vec<Vec4Data<float> > const &other)
			{
				return operate(v, other, std::plus<float>());
			}
			
			virtual Vec<Vec4Data<float> > &add(Vec<Vec4Data<float> > &v, float single)
			{
				return operate(v, single, std::plus<float>());
			}
			
			virtual Vec<Vec4Data<float> > &add(Vec<Vec4Data<float> > &v, Vec<Vec4Data<float> > const &other)
			{
				return operate(v, other, std::plus<float>());
			}
			
			/* substraction */
			virtual Vec<Vec4Data<float> > substract(Vec<Vec4Data<float> > const &v, float single) 
			{
				return operate(v, single, std::minus<float>());
			}
			
			virtual Vec<Vec4Data<float> > substract(Vec<Vec4Data<float> > const &v, Vec<Vec4Data<float> > const &other)
			{
				return operate(v, other, std::minus<float>());
			}
			
			virtual Vec<Vec4Data<float> > &substract(Vec<Vec4Data<float> > &v, float single)
			{
				return operate(v, single, std::minus<float>());
			}
			
			virtual Vec<Vec4Data<float> > &substract(Vec<Vec4Data<float> > &v, Vec<Vec4Data<float> > const &other)
			{
				return operate(v, other, std::minus<float>());
			}

			/* multiplication */
			virtual Vec<Vec4Data<float> > multiply(Vec<Vec4Data<float> > const &v, float single) 
			{
				return operate(v, single, std::multiplies<float>());
			}
			
			virtual Vec<Vec4Data<float> > multiply(Vec<Vec4Data<float> > const &v, Vec<Vec4Data<float> > const &other)
			{
				return operate(v, other, std::multiplies<float>());
			}
			
			virtual Vec<Vec4Data<float> > &multiply(Vec<Vec4Data<float> > &v, float single)
			{
				return operate(v, single, std::multiplies<float>());
			}
			
			virtual Vec<Vec4Data<float> > &multiply(Vec<Vec4Data<float> > &v, Vec<Vec4Data<float> > const &other)
			{
				return operate(v, other, std::multiplies<float>());
			}

			/* division */
			virtual Vec<Vec4Data<float> > divide(Vec<Vec4Data<float> > const &v, float single) 
			{
				return operate(v, single, std::divides<float>());
			}
			
			virtual Vec<Vec4Data<float> > divide(Vec<Vec4Data<float> > const &v, Vec<Vec4Data<float> > const &other)
			{
				return operate(v, other, std::divides<float>());
			}
			
			virtual Vec<Vec4Data<float> > &divide(Vec<Vec4Data<float> > &v, float single)
			{
				return operate(v, single, std::divides<float>());
			}
			
			virtual Vec<Vec4Data<float> > &divide(Vec<Vec4Data<float> > &v, Vec<Vec4Data<float> > const &other)
			{
				return operate(v, other, std::divides<float>());
			}

			virtual float length(Vec<Vec4Data<float> > const &v)
			{
				return sqrt(dot(v, v));
			}

			virtual Vec<Vec4Data<float> > normalize(Vec<Vec4Data<float> > const &v)
			{
				return divide(v, length(v));
			}
			
			virtual Vec<Vec4Data<float> > &normalize(Vec<Vec4Data<float> > &v)
			{
				
				return divide(v, length(v));
			}
			
			virtual Vec<Vec4Data<float> > invert(Vec<Vec4Data<float> > const &v)
			{
				return multiply(v, -1);
			}
			
			virtual Vec<Vec4Data<float> > &invert(Vec<Vec4Data<float> > &v)
			{
				return multiply(v, -1);
			}
		
			virtual float dot(Vec<Vec4Data<float> > const &v, Vec<Vec4Data<float> > const &other)
			{
				return v.values[0] * other.values[0] +
					   v.values[1] * other.values[1] +
					   v.values[2] * other.values[2] +
					   v.values[3] * other.values[3];
			}
		private:
			template <typename Operator>
			inline Vec<Vec4Data<float> >operate(Vec<Vec4Data<float> > const &v, Vec<Vec4Data<float> > const &other, Operator op) const
			{
				Vec<Vec4Data<float> > copy;

				for (size_t i = 0; i < 4; ++i)
					copy.values[i] = op(v.values[i], other.values[i]);
				
				return copy;
			}

			template <typename Operator>
			inline Vec<Vec4Data<float> > operate(Vec<Vec4Data<float> > const &v, float single, Operator op)
			{
				Vec<Vec4Data<float> > copy;

				for (size_t i = 0; i < 4; ++i)
					copy.values[i] = op(v.values[i], single);
				
				return copy;
			}

			template <typename Operator>
			inline Vec<Vec4Data<float> > &operate(Vec<Vec4Data<float> > &v, float single, Operator op)
			{
				for (size_t i = 0; i < 4; ++i)
					v.values[i] = op(v.values[i], single);
				
				return v;
			}

			template <typename Operator>
			inline Vec<Vec4Data<float> > &operate(Vec<Vec4Data<float> > &v, Vec<Vec4Data<float> > const &other, Operator op)
			{			
				for (size_t i = 0; i < 4; ++i)
					v.values[i] = op(v.values[i], other.values[i]);
				
				return v;
			}
	};
}

}

#endif /* __MATH_SSE_FLOAT4_IMPL_H__ */

