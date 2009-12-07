#ifndef __JESSEVDK_MATH_SSE_FLOAT4_H__
#define __JESSEVDK_MATH_SSE_FLOAT4_H__

#ifdef JESSEVDK_ENABLE_SSE
#include <xmmintrin.h>
#include <jessevdk/math/vec.hh>
#include <jessevdk/math/sse/implementation.hh>

namespace jessevdk
{
namespace math
{
	template <>
	struct Vec4Data<float> : TypeDefine<float, 4>
	{
		union {
			/* sse register */
			__m128 _ssevec;

			float values[4];
			struct {
				float x;
				float y;

				union {
					struct {
						float z;
						float w;
					};
					struct {
						float width;
						float height;
					};
				};
			};
			struct {
				float r;
				float g;
				float b;
				float a;
			};
			struct {
				Vec2<float> xy;
				Vec2<float>zw;
			};
			struct {
				Vec2<float> rg;
				Vec2<float> ba;
			};
			struct {
				Vec3<float> xyz;
				float _wpad;
			};
			struct {
				Vec3<float> rgb;
				float _apad;
			};
		};
	};

	template <>
	struct Vec<Vec4Data<float> > : Vec4Data<float>
	{
		static sse::Implementation *s_implementation;

		float Sum() const
		{
			return s_implementation->Sum(*this);
		}

		float operator[](size_t idx) const
		{
			return s_implementation->Index(*this, idx);
		}

		float &operator[](size_t idx)
		{
			return s_implementation->Index(*this, idx);
		}

		Vec<Vec4Data<float> > operator+(float single) const
		{
			return s_implementation->Add(*this, single);
		}

		Vec<Vec4Data<float> > operator+(Vec<Vec4Data<float> > const &other) const
		{
			return s_implementation->Add(*this, other);
		}

		Vec<Vec4Data<float> > &operator+=(float single)
		{
			return s_implementation->Add(*this, single);
		}

		Vec<Vec4Data<float> > &operator+=(Vec<Vec4Data<float> > const &other)
		{
			return s_implementation->Add(*this, other);
		}

		Vec<Vec4Data<float> > operator-(float single) const
		{
			return s_implementation->Substract(*this, single);
		}

		Vec<Vec4Data<float> > operator-(Vec<Vec4Data<float> > const &other) const
		{
			return s_implementation->Substract(*this, other);
		}

		Vec<Vec4Data<float> > &operator-=(float single)
		{
			return s_implementation->Substract(*this, single);
		}

		Vec<Vec4Data<float> > &operator-=(Vec<Vec4Data<float> > const &other)
		{
			return s_implementation->Substract(*this, other);
		}

		Vec<Vec4Data<float> > operator*(float single) const
		{
			return s_implementation->Multiply(*this, single);
		}

		Vec<Vec4Data<float> > operator*(Vec<Vec4Data<float> > const &other) const
		{
			return s_implementation->Multiply(*this, other);
		}

		Vec<Vec4Data<float> > &operator*=(float single)
		{
			return s_implementation->Multiply(*this, single);
		}

		Vec<Vec4Data<float> > &operator*=(Vec<Vec4Data<float> > const &other)
		{
			return s_implementation->Multiply(*this, other);
		}

		Vec<Vec4Data<float> > operator/(float single) const
		{
			return s_implementation->Divide(*this, single);
		}

		inline Vec<Vec4Data<float> > operator/(Vec<Vec4Data<float> > const &other) const
		{
			return s_implementation->Divide(*this, other);
		}

		inline Vec<Vec4Data<float> > &operator/=(float single)
		{
			return s_implementation->Divide(*this, single);
		}

		inline Vec<Vec4Data<float> > &operator/=(Vec<Vec4Data<float> > const &other)
		{
			return s_implementation->Divide(*this, other);
		}

		float Length() const
		{
			return s_implementation->Length(*this);
		}

		Vec<Vec4Data<float> > &Normalize()
		{
			return s_implementation->Normalize(*this);
		}

		Vec<Vec4Data<float> > Normalize() const
		{
			return s_implementation->Normalize(*this);
		}

		Vec<Vec4Data<float> > &Invert()
		{
			return s_implementation->Invert(*this);
		}

		Vec<Vec4Data<float> > Invert() const
		{
			return s_implementation->Invert(*this);
		}

		float Dot(Vec<Vec4Data<float> > const &other) const
		{
			return s_implementation->Dot(*this, other);
		}
	};
}
}

#endif

#endif /* __JESSEVDK_MATH_SSE_FLOAT4_H__ */

