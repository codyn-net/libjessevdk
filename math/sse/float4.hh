#ifndef __MATH_SSE_FLOAT4_H__
#define __MATH_SSE_FLOAT4_H__

#include <xmmintrin.h>
#include "../vec.hh"
#include "implementation.hh"

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

		float sum() const
		{
			return s_implementation->sum(*this);
		}

		float operator[](size_t idx) const
		{
			return s_implementation->index(*this, idx);
		}
		
		float &operator[](size_t idx)
		{
			return s_implementation->index(*this, idx);
		}
		
		Vec<Vec4Data<float> > operator+(float single) const
		{
			return s_implementation->add(*this, single);
		}
		
		Vec<Vec4Data<float> > operator+(Vec<Vec4Data<float> > const &other) const
		{
			return s_implementation->add(*this, other);
		}
		
		Vec<Vec4Data<float> > &operator+=(float single)
		{
			return s_implementation->add(*this, single);
		}
		
		Vec<Vec4Data<float> > &operator+=(Vec<Vec4Data<float> > const &other)
		{
			return s_implementation->add(*this, other);
		}
		
		Vec<Vec4Data<float> > operator-(float single) const
		{
			return s_implementation->substract(*this, single);
		}
		
		Vec<Vec4Data<float> > operator-(Vec<Vec4Data<float> > const &other) const
		{
			return s_implementation->substract(*this, other);
		}
		
		Vec<Vec4Data<float> > &operator-=(float single)
		{
			return s_implementation->substract(*this, single);
		}
		
		Vec<Vec4Data<float> > &operator-=(Vec<Vec4Data<float> > const &other)
		{
			return s_implementation->substract(*this, other);
		}
		
		Vec<Vec4Data<float> > operator*(float single) const
		{
			return s_implementation->multiply(*this, single);
		}
		
		Vec<Vec4Data<float> > operator*(Vec<Vec4Data<float> > const &other) const
		{
			return s_implementation->multiply(*this, other);
		}
		
		Vec<Vec4Data<float> > &operator*=(float single)
		{
			return s_implementation->multiply(*this, single);
		}
		
		Vec<Vec4Data<float> > &operator*=(Vec<Vec4Data<float> > const &other)
		{
			return s_implementation->multiply(*this, other);
		}
		
		Vec<Vec4Data<float> > operator/(float single) const
		{
			return s_implementation->divide(*this, single);
		}
		
		inline Vec<Vec4Data<float> > operator/(Vec<Vec4Data<float> > const &other) const
		{
			return s_implementation->divide(*this, other);
		}
		
		inline Vec<Vec4Data<float> > &operator/=(float single)
		{
			return s_implementation->divide(*this, single);
		}
		
		inline Vec<Vec4Data<float> > &operator/=(Vec<Vec4Data<float> > const &other)
		{
			return s_implementation->divide(*this, other);
		}
		
		float length() const
		{
			return s_implementation->length(*this);
		}
		
		Vec<Vec4Data<float> > &normalize()
		{
			return s_implementation->normalize(*this);
		}
		
		Vec<Vec4Data<float> > normalize() const
		{
			return s_implementation->normalize(*this);
		}
		
		Vec<Vec4Data<float> > &invert()
		{
			return s_implementation->invert(*this);
		}
		
		Vec<Vec4Data<float> > invert() const
		{
			return s_implementation->invert(*this);
		}
		
		float dot(Vec<Vec4Data<float> > const &other) const
		{
			return s_implementation->dot(*this, other);
		}
	};
}

#endif /* __MATH_SSE_FLOAT4_H__ */

