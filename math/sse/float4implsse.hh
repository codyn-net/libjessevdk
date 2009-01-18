#ifndef __MATH_SSE_FLOAT4_IMPL_SSE_H__
#define __MATH_SSE_FLOAT4_IMPL_SSE_H__

#include "float4impl.hh"

namespace math
{
namespace sse
{
	class Float4ImplSSE : public Float4Impl
	{
		typedef Vec<Vec4Data<float> > Type;

		public:
			/* addition */
			virtual Type add(Type const &v, float single) 
			{
				Type copy = create(single, single, single, single);
				
				copy._ssevec = _mm_add_ps(v._ssevec, copy._ssevec);
				return copy;
			}
			
			virtual Type add(Type const &v, Type const &other)
			{
				Type copy;
				
				copy._ssevec = _mm_add_ps(v._ssevec, other._ssevec);
				return copy;
			}
			
			virtual Type &add(Type &v, float single)
			{
				__m128 r = _mm_set_ps(single, single, single, single);
				
				v._ssevec = _mm_add_ps(v._ssevec, r);
				return v;
			}
			
			virtual Type &add(Type &v, Type const &other)
			{
				v._ssevec = _mm_add_ps(v._ssevec, other._ssevec);
				return v;
			}
			
			/* substraction */
			virtual Type substract(Type const &v, float single) 
			{
				Type copy = create(single, single, single, single);
				
				copy._ssevec = _mm_sub_ps(v._ssevec, copy._ssevec);
				return copy;
			}
			
			virtual Type substract(Type const &v, Type const &other)
			{
				Type copy;
				
				copy._ssevec = _mm_sub_ps(v._ssevec, other._ssevec);
				return copy;
			}
			
			virtual Type &substract(Type &v, float single)
			{
				__m128 r = _mm_set_ps(single, single, single, single);
				
				v._ssevec = _mm_sub_ps(v._ssevec, r);
				return v;
			}
			
			virtual Type &substract(Type &v, Type const &other)
			{
				v._ssevec = _mm_sub_ps(v._ssevec, other._ssevec);
				return v;
			}

			/* multiplication */
			virtual Type multiply(Type const &v, float single) 
			{
				Type copy = create(single, single, single, single);
				
				copy._ssevec = _mm_mul_ps(v._ssevec, copy._ssevec);
				return copy;
			}
			
			virtual Type multiply(Type const &v, Type const &other)
			{
				Type copy;
				
				copy._ssevec = _mm_mul_ps(v._ssevec, other._ssevec);
				return copy;
			}
			
			virtual Type &multiply(Type &v, float single)
			{
				__m128 r = _mm_set_ps(single, single, single, single);
				
				v._ssevec = _mm_mul_ps(v._ssevec, r);
				return v;
			}
			
			virtual Type &multiply(Type &v, Type const &other)
			{
				v._ssevec = _mm_mul_ps(v._ssevec, other._ssevec);
				return v;
			}

			/* division */
			virtual Type divide(Type const &v, float single) 
			{
				Type copy = create(single, single, single, single);
				
				copy._ssevec = _mm_div_ps(v._ssevec, copy._ssevec);
				return copy;
			}
			
			virtual Type divide(Type const &v, Type const &other)
			{
				Type copy;
				
				copy._ssevec = _mm_div_ps(v._ssevec, other._ssevec);
				return copy;
			}
			
			virtual Type &divide(Type &v, float single)
			{
				__m128 r = _mm_set_ps(single, single, single, single);
				
				v._ssevec = _mm_div_ps(v._ssevec, r);
				return v;
			}
			
			virtual Type &divide(Type &v, Type const &other)
			{
				v._ssevec = _mm_div_ps(v._ssevec, other._ssevec);
				return v;
			}

			virtual float length(Type const &v)
			{
				__m128 r = _mm_set_ss(dot(v, v));
				r = _mm_sqrt_ps(r);

				return *(float *)&r;
			}

			virtual Type normalize(Type const &v)
			{
				__m128 r = _mm_set_ss(dot(v, v));
				r = _mm_rsqrt_ss(r);

				return multiply(v, *(float *)&r);
			}
			
			virtual Type &normalize(Type &v)
			{
				__m128 r = _mm_set_ss(dot(v, v));
				r = _mm_rsqrt_ss(r);

				return multiply(v, *(float *)&r);
			}
			
			virtual Type invert(Type const &v)
			{
				Type copy = create(-1, -1, -1, -1);
				
				copy._ssevec = _mm_mul_ps(v._ssevec, copy._ssevec);
				return copy;
			}
			
			virtual Type &invert(Type &v)
			{
				Type copy = create(-1, -1, -1, -1);
				
				v._ssevec = _mm_mul_ps(v._ssevec, copy._ssevec);
				return v;
			}
		
			virtual float dot(Type const &v, Type const &other)
			{
				
			}
		private:
			Type create(float x, float y, float z, float w)
			{
				float v[4] = {x, y, z, w};
				
				return *reinterpret_cast<Type *>(v);
			}
	};
}

}

#endif /* __MATH_SSE_FLOAT4_IMPL_SSE_H__ */

