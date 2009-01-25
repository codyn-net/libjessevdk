#ifndef __MATH_VEC_H__
#define __MATH_VEC_H__

#include <numeric>
#include <algorithm>
#include <functional>
#include <cmath>
#include <ostream>

#include "operators.hh"
#include "types.hh"

namespace math
{
	template <typename Base>
	struct Vec : Base
	{
		typedef Operators<Vec<Base> > Operator;

		inline typename Base::type sum() const
		{
			return std::accumulate(Base::values, Base::values + Base::size, 0, Operator::adder);
		}
		
		inline typename Base::type minsum() const
		{
			return std::accumulate(Base::values + 1, Base::values + Base::size, Base::values[0], Operator::substractor);
		}
		
		inline typename Base::type operator[](size_t idx) const
		{
			return *((typename Base::type *)this + idx);
		}
		
		inline typename Base::type &operator[](size_t idx)
		{
			return *((typename Base::type *)this + idx);
		}
		
		inline Vec<Base> operator+(typename Base::type single) const
		{
			return Operator::operate(*this, single, Operator::adder);
		}
		
		inline Vec<Base> operator+(Vec<Base> const &other) const
		{
			return Operator::operate(*this, other, Operator::adder);
		}
		
		inline Vec<Base> &operator+=(typename Base::type single)
		{
			return Operator::operate(*this, single, Operator::adder);
		}
		
		inline Vec<Base> &operator+=(Vec<Base> const &other)
		{
			return Operator::operate(*this, other, Operator::adder);
		}
		
		inline Vec<Base> operator-(typename Base::type single) const
		{
			return Operator::operate(*this, single, Operator::substractor);
		}
		
		inline Vec<Base> operator-(Vec<Base> const &other) const
		{
			return Operator::operate(*this, other, Operator::substractor);
		}
		
		inline Vec<Base> &operator-=(typename Base::type single)
		{
			return Operator::operate(*this, single, Operator::substractor);
		}
		
		inline Vec<Base> &operator-=(Vec<Base> const &other)
		{
			return Operator::operate(*this, other, Operator::substractor);
		}
		
		inline Vec<Base> operator*(typename Base::type single) const
		{
			return Operator::operate(*this, single, Operator::multiplier);
		}
		
		inline Vec<Base> operator*(Vec<Base> const &other) const
		{
			return Operator::operate(*this, other, Operator::multiplier);
		}
		
		inline Vec<Base> &operator*=(typename Base::type single)
		{
			return Operator::operate(*this, single, Operator::multiplier);
		}
		
		inline Vec<Base> &operator*=(Vec<Base> const &other)
		{
			return Operator::operate(*this, other, Operator::multiplier);
		}
		
		inline Vec<Base> operator/(typename Base::type single) const
		{
			return Operator::operate(*this, single, Operator::divider);
		}
		
		inline Vec<Base> operator/(Vec<Base> const &other) const
		{
			return Operator::operate(*this, other, Operator::divider);
		}
		
		inline Vec<Base> &operator/=(typename Base::type single)
		{
			return Operator::operate(*this, single, Operator::divider);
		}
		
		inline Vec<Base> &operator/=(Vec<Base> const &other)
		{
			return Operator::operate(*this, other, Operator::divider);
		}
		
		inline Vec<Base> operator%(typename Base::type single) const
		{
			return Operator::operate(*this, single, Operator::modulator);
		}
		
		inline Vec<Base> operator%(Vec<Base> const &other) const
		{
			return Operator::operate(*this, other, Operator::modulator);
		}
		
		inline Vec<Base> &operator%=(typename Base::type single)
		{
			return Operator::operate(*this, single, Operator::modulator);
		}
		
		inline Vec<Base> &operator%=(Vec<Base> const &other)
		{
			return Operator::operate(*this, other, Operator::modulator);
		}

		inline Vec<Base> operator-() const
		{
			return Operator::operate(*this, -1, Operator::multiplier);
		}
		
		inline typename Base::type length() const
		{
			return sqrt(dot(*this));
		}
		
		inline typename Base::type nsqrt(typename Base::type val) const
		{
			return 1 / sqrt(val);
		}
		
		inline Vec<Base> &normalize()
		{
			*this = *this * nsqrt(dot(*this));
			return *this;
		}
		
		inline Vec<Base> normalize() const
		{
			return *this * nsqrt(dot(*this));
		}
		
		inline Vec<Base> &invert()
		{
			*this = *this * -1;
			return *this;
		}
		
		inline Vec<Base> invert() const
		{
			return *this * -1;
		}
		
		inline typename Base::type dot(Vec<Base> const &other) const
		{
			typename Base::type d = 0;
			
			for (size_t i = 0; i < Base::size; ++i)
				d += Base::values[i] * other.values[i];
			
			return d;
		}
	};
	
	template <typename Base>
	std::ostream &operator<<(std::ostream &stream, Vec<Base> const &f)
	{
		stream << "[";
		
		for (size_t i = 0; i < Base::size; ++i)
			stream << ((Base &)f).values[i] << (i != Base::size - 1 ? ", " : "");
		
		return stream << "]";
	};
	
	template <typename Type>
	struct Vec2Data : TypeDefine<Type, 2>
	{
		union {
			Type values[2];
			struct {
				Type x;
				Type y;
			};
			struct {
				Type z;
				Type w;
			};
			struct {
				Type width;
				Type height;
			};
			struct {
				Type s;
				Type t;
			};
			struct {
				Type u;
				Type v;
			};
		};
		
		static Vec<Vec2Data<Type> > empty;
		static Vec<Vec2Data<Type> > zeros;
		static Vec<Vec2Data<Type> > ones;
	};

	template <typename Type>
	struct Vec2 : Vec<Vec2Data<Type> > 
	{
	};
	
	template <typename Type>
	struct vec2 : Vec2<Type> 
	{
		vec2()
		{
		}
		
		vec2(Type x, Type y)
		{
			Vec2<Type>::values[0] = x; 
			Vec2<Type>::values[1] = y;
		}
		
		vec2(Type const (&vals)[2])
		:
			Vec2<Type>(reinterpret_cast<Vec2<Type> const &>(vals))
		{
		}
		
		vec2(Vec2Data<Type> const &other)
		:
			Vec2<Type>(static_cast<Vec2<Type> const &>(other))
		{
		};
	};
	
	template <typename Type>
	Vec<Vec2Data<Type> > Vec2Data<Type>::empty = vec2<Type>(0, 0);
	
	template <typename Type>
	Vec<Vec2Data<Type> > Vec2Data<Type>::zeros = Vec2Data<Type>::empty;
	
	template <typename Type>
	Vec<Vec2Data<Type> > Vec2Data<Type>::ones = vec2<Type>(1, 1);
	
	template <typename Type>
	struct Vec3Data : TypeDefine<Type, 3>
	{		 
		union {
			Type values[3];
			struct {
				Type x;
				Type y;
				Type z;
			};
			struct {
				Type r;
				Type g;
				Type b;
			};
			struct {
				Vec2<Type> xy;
				Type _zpad;
			};
			struct {
				Type _xpad;
				Vec2<Type> yz;
			};
		};
		
		Vec<Vec3Data<Type> > cross(Vec<Vec3Data<Type> > const &other) const
		{
			Vec<Vec3Data<Type> > c;
			Vec3Data<Type> &o = ((Vec3Data<Type> &)other);
			
			c.x = values[1] * o.values[2] - values[2] * o.values[1];
			c.y = values[2] * o.values[0] - values[0] * o.values[2];
			c.z = values[0] * o.values[1] - values[1] * o.values[0];
			
			return c;
		}
		
		static Vec<Vec3Data<Type> > empty;
		static Vec<Vec3Data<Type> > zeros;
		static Vec<Vec3Data<Type> > ones;
	};
	
	template <typename Type>
	struct Vec3 : Vec<Vec3Data<Type> > 
	{
	};
	
	template <typename Type>
	struct vec3 : Vec3<Type>
	{
		vec3()
		{
		}
		
		vec3(Type x, Type y, Type z)
		{
			Vec3<Type>::values[0] = x;
			Vec3<Type>::values[1] = y;
			Vec3<Type>::values[2] = z;
		}
		
		vec3(Vec2Data<Type> const &xy, Type z)
		{
			Vec3<Type>::values[0] = xy.x;
			Vec3<Type>::values[1] = xy.y;
			Vec3<Type>::values[2] = z;
		}
		
		vec3(Type x, Vec2Data<Type> const &yz)
		{
			Vec3<Type>::values[0] = x;
			Vec3<Type>::values[1] = yz.x;
			Vec3<Type>::values[2] = yz.y;
		}
		
		vec3(Type const (&vals)[3])
		:
			Vec3<Type>(reinterpret_cast<Vec3<Type> const &>(vals))
		{
		}
		
		vec3(Vec3Data<Type> const &other)
		:
			Vec3<Type>(static_cast<Vec3<Type> const &>(other))
		{
		}
	};
	
	template <typename Type>
	Vec<Vec3Data<Type> > Vec3Data<Type>::empty = vec3<Type>(0, 0, 0);
	
	template <typename Type>
	Vec<Vec3Data<Type> > Vec3Data<Type>::zeros = Vec3Data<Type>::empty;
	
	template <typename Type>
	Vec<Vec3Data<Type> > Vec3Data<Type>::ones = vec3<Type>(1, 1, 1);

	template <typename Type>
	struct Vec4Data : TypeDefine<Type, 4>
	{		
		union {
			Type values[4];
			struct {
				Type x;
				Type y;
			
				union {
					struct { 
						Type z;
						Type w;
					};
					struct {
						Type width;
						Type height;
					};
				};
			};
			struct {
				Type r;
				Type g;
				Type b;
				Type a;
			};
			struct {
				Vec2<Type> xy;
				Vec2<Type>zw;
			};
			struct {
				Vec2<Type> rg;
				Vec2<Type> ba;
			};
			struct {
				Vec3<Type> xyz;
				Type _wpad;
			};
			struct {
				Vec3<Type> rgb;
				Type _apad;
			};
		};
		
		static Vec<Vec4Data<Type> > zeros;
		static Vec<Vec4Data<Type> > empty;
		static Vec<Vec4Data<Type> > ones;
	};
	
	template <typename Type>
	struct Vec4 : Vec<Vec4Data<Type> > 
	{
	};

	template <typename Type>
	struct vec4 : Vec4<Type>
	{
		vec4()
		{
		}
		
		vec4(Type x, Type y, Type z, Type w)
		{
			Vec4Data<Type>::values[0] = x; 
			Vec4Data<Type>::values[1] = y; 
			Vec4Data<Type>::values[2] = z; 
			Vec4Data<Type>::values[3] = w;
		}
		
		vec4(Type const (&vals)[4])
		:
			Vec4<Type>(reinterpret_cast<Vec4<Type> const &>(vals))
		{
		}
		
		vec4(Vec4Data<Type> const &other)
		:
			Vec4<Type>(static_cast<Vec4<Type> const &>(other))
		{
		}
	};
	
	template <typename Type>
	Vec<Vec4Data<Type> > Vec4Data<Type>::empty = vec4<Type>(0, 0, 0, 0);
	
	template <typename Type>
	Vec<Vec4Data<Type> > Vec4Data<Type>::zeros = Vec4Data<Type>::empty;
	
	template <typename Type>
	Vec<Vec4Data<Type> > Vec4Data<Type>::ones = vec4<Type>(1, 1, 1, 1);
		
	template <typename Type, size_t Size>
	struct VecData : TypeDefine<Type, Size>
	{
		Type values[Size];
	};
	
	template <typename Type, size_t Size>
	struct vec : Vec<VecData<Type, Size> >
	{
	};
}

#endif /* __MATH_VEC_H__ */

