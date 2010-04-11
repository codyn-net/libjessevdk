#ifndef __JESSEVDK_MATH_SSE_FLOAT4_IMPL_SSE_H__
#define __JESSEVDK_MATH_SSE_FLOAT4_IMPL_SSE_H__

#include <jessevdk/math/sse/float4impl.hh>

namespace jessevdk
{
namespace math
{
namespace sse
{
	class Float4ImplSSE : public Float4Impl
	{
		typedef Vec<Vec4Data<float> > Type;

		public:
			/* addition */
			virtual Type Add(Type const &v, float single)
			{
				Type copy = Create(single, single, single, single);

				copy._ssevec = _mm_add_ps(v._ssevec, copy._ssevec);
				return copy;
			}

			virtual Type Add(Type const &v, Type const &other)
			{
				Type copy;

				copy._ssevec = _mm_add_ps(v._ssevec, other._ssevec);
				return copy;
			}

			virtual Type &Add(Type &v, float single)
			{
				__m128 r = _mm_set_ps(single, single, single, single);

				v._ssevec = _mm_add_ps(v._ssevec, r);
				return v;
			}

			virtual Type &Add(Type &v, Type const &other)
			{
				v._ssevec = _mm_add_ps(v._ssevec, other._ssevec);
				return v;
			}

			/* substraction */
			virtual Type Substract(Type const &v, float single)
			{
				Type copy = Create(single, single, single, single);

				copy._ssevec = _mm_sub_ps(v._ssevec, copy._ssevec);
				return copy;
			}

			virtual Type Substract(Type const &v, Type const &other)
			{
				Type copy;

				copy._ssevec = _mm_sub_ps(v._ssevec, other._ssevec);
				return copy;
			}

			virtual Type &Substract(Type &v, float single)
			{
				__m128 r = _mm_set_ps(single, single, single, single);

				v._ssevec = _mm_sub_ps(v._ssevec, r);
				return v;
			}

			virtual Type &Substract(Type &v, Type const &other)
			{
				v._ssevec = _mm_sub_ps(v._ssevec, other._ssevec);
				return v;
			}

			/* multiplication */
			virtual Type Multiply(Type const &v, float single)
			{
				Type copy = Create(single, single, single, single);

				copy._ssevec = _mm_mul_ps(v._ssevec, copy._ssevec);
				return copy;
			}

			virtual Type Multiply(Type const &v, Type const &other)
			{
				Type copy;

				copy._ssevec = _mm_mul_ps(v._ssevec, other._ssevec);
				return copy;
			}

			virtual Type &Multiply(Type &v, float single)
			{
				__m128 r = _mm_set_ps(single, single, single, single);

				v._ssevec = _mm_mul_ps(v._ssevec, r);
				return v;
			}

			virtual Type &Multiply(Type &v, Type const &other)
			{
				v._ssevec = _mm_mul_ps(v._ssevec, other._ssevec);
				return v;
			}

			/* division */
			virtual Type Divide(Type const &v, float single)
			{
				Type copy = Create(single, single, single, single);

				copy._ssevec = _mm_div_ps(v._ssevec, copy._ssevec);
				return copy;
			}

			virtual Type Divide(Type const &v, Type const &other)
			{
				Type copy;

				copy._ssevec = _mm_div_ps(v._ssevec, other._ssevec);
				return copy;
			}

			virtual Type &Divide(Type &v, float single)
			{
				__m128 r = _mm_set_ps(single, single, single, single);

				v._ssevec = _mm_div_ps(v._ssevec, r);
				return v;
			}

			virtual Type &Divide(Type &v, Type const &other)
			{
				v._ssevec = _mm_div_ps(v._ssevec, other._ssevec);
				return v;
			}

			virtual float Length(Type const &v)
			{
				__m128 r = _mm_set_ss(Dot(v, v));
				r = _mm_sqrt_ps(r);

				return *(float *)&r;
			}

			virtual Type Normalize(Type const &v)
			{
				__m128 r = _mm_set_ss(Dot(v, v));
				r = _mm_rsqrt_ss(r);

				return Multiply(v, *(float *)&r);
			}

			virtual Type &Normalize(Type &v)
			{
				__m128 r = _mm_set_ss(Dot(v, v));
				r = _mm_rsqrt_ss(r);

				return Multiply(v, *(float *)&r);
			}

			virtual Type Invert(Type const &v)
			{
				Type copy = Create(-1, -1, -1, -1);

				copy._ssevec = _mm_mul_ps(v._ssevec, copy._ssevec);
				return copy;
			}

			virtual Type &Invert(Type &v)
			{
				Type copy = Create(-1, -1, -1, -1);

				v._ssevec = _mm_mul_ps(v._ssevec, copy._ssevec);
				return v;
			}

			virtual float Dot(Type const &v, Type const &other)
			{

			}
		private:
			Type Create(float x, float y, float z, float w)
			{
				float v[4] = {x, y, z, w};

				return *reinterpret_cast<Type *>(v);
			}
	};
}
}
}

#endif /* __JESSEVDK_MATH_SSE_FLOAT4_IMPL_SSE_H__ */

