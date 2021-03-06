#ifndef __JESSEVDK_MATH_MAT_H__
#define __JESSEVDK_MATH_MAT_H__

#include <ostream>
#include <iostream>

#include <jessevdk/math/operators.hh>
#include <jessevdk/math/types.hh>
#include <jessevdk/math/vec.hh>

namespace jessevdk
{
namespace math
{
	template <typename Base>
	struct Mat : Base
	{
		typedef Operators<Mat<Base> > Operator;
		typedef vec<typename Base::type, Base::half_size> Vector;

		Mat<Base> &operator*=(Mat<Base> const &other);

		inline typename Base::type operator[](size_t idx) const
		{
			return *((typename Base::type *)this + idx);
		}

		inline typename Base::type &operator[](size_t idx)
		{
			return *((typename Base::type *)this + idx);
		}

		inline Mat<Base> &operator/=(Mat<Base> const &other)
		{
			return Operator::Operate(*this, other, Operator::Divider);
		}

		inline Mat<Base> &operator%=(Mat<Base> const &other)
		{
			return Operator::Operate(*this, other, Operator::Modulator);
		}

		inline Mat<Base> &operator+=(Mat<Base> const &other)
		{
			return Operator::Operate(*this, other, Operator::Adder);
		}

		inline Mat<Base> &operator-=(Mat<Base> const &other)
		{
			return Operator::Operate(*this, other, Operator::Substractor);
		}

		inline Mat<Base> &operator*=(typename Base::type single)
		{
			return Operator::Operate(*this, single, Operator::Multiplier);
		}

		inline Mat<Base> &operator/=(typename Base::type single)
		{
			return Operator::Operate(*this, single, Operator::Divider);
		}

		inline Mat<Base> &operator%=(typename Base::type single)
		{
			return Operator::Operate(*this, single, Operator::Modulator);
		}

		inline Mat<Base> &operator+=(typename Base::type single)
		{
			return Operator::Operate(*this, single, Operator::Adder);
		}

		inline Mat<Base> &operator-=(typename Base::type single)
		{
			return Operator::Operate(*this, single, Operator::Substractor);
		}

		inline Mat<Base> operator/(Mat<Base> const &other) const
		{
			return Operator::Operate(*this, other, Operator::Divider);
		}

		inline Mat<Base> operator%(Mat<Base> const &other) const
		{
			return Operator::Operate(*this, other, Operator::Modulator);
		}

		inline Mat<Base> operator+(Mat<Base> const &other) const
		{
			return Operator::Operate(*this, other, Operator::Adder);
		}

		inline Mat<Base> operator-(Mat<Base> const &other) const
		{
			return Operator::Operate(*this, other, Operator::Substractor);
		}

		inline Mat<Base> operator/(typename Base::type single) const
		{
			return Operator::Operate(*this, single, Operator::Divider);
		}

		inline Mat<Base> operator%(typename Base::type single) const
		{
			return Operator::Operate(*this, single, Operator::Modulator);
		}

		inline Mat<Base> operator+(typename Base::type single) const
		{
			return Operator::Operate(*this, single, Operator::Adder);
		}

		inline Mat<Base> operator-(typename Base::type single) const
		{
			return Operator::Operate(*this, single, Operator::Substractor);
		}

		inline Mat<Base> operator-() const
		{
			return Operator::Operate(*this, -1, Operator::Substractor);
		}

		Mat<Base> &Transpose();
		inline Mat<Base> Transpose() const
		{
			Mat<Base> copy(*this);
			return copy.Transpose();
		}
	};

	template <typename Base>
	std::ostream &operator<<(std::ostream &stream, Mat<Base> const &m)
	{
		for (size_t i = 0; i < Base::half_size; ++i)
		{
			stream << "[";

			for (size_t j = 0; j < Base::half_size; ++j)
			{
				size_t idx = j * Base::half_size + i;
				stream << m.values[idx] << (j != Base::half_size - 1 ? ", " : "");
			}

			stream << "]";

			if (i != Base::half_size - 1)
				stream << std::endl;
		}

		return stream;
	};

	template <typename Base>
	Mat<Base> &Mat<Base>::operator*=(Mat<Base> const &other)
	{
		Mat<Base> copy(*this);

		*this = copy * other;
		return *this;
	}

	template <typename Base>
	Mat<Base> &Mat<Base>::Transpose()
	{
		for (unsigned y = 1; y < Base::half_size; ++y)
		{
			for (unsigned x = 0; x < y; ++x)
			{
				size_t i1 = y * Base::half_size + x;
				size_t i2 = x * Base::half_size + y;

				typename Base::type tmp = Base::values[i1];
				Base::values[i1] = Base::values[i2];
				Base::values[i2] = tmp;
			}
		}

		return *this;
	}

	template <typename Type, size_t Size>
	struct MatTypeDefine : TypeDefine<Type, Size * Size>
	{
		enum
		{
			half_size = Size
		};
	};

	template <typename Type>
	struct Mat2Data : MatTypeDefine<Type, 2>
	{
		typedef Operators<Mat<Mat2Data<Type> > > Operator;

		union
		{
			Type values[4];

			struct
			{
				Vec<Vec2Data<Type> > x;
				Vec<Vec2Data<Type> > y;
			};
		};

		Mat<Mat2Data<Type> > operator*(Mat2Data<Type> const &other) const;

		Mat<Mat2Data<Type> > operator*(Type single) const
		{
			return Operator::Operate(static_cast<Mat<Mat2Data<Type> > const &>(*this), single, Operator::Multiplier);
		}

		Mat<Mat2Data<Type> > Inverse() const;
		Mat<Mat2Data<Type> > &Invert();

		Type Determinant() const;
		Type Det() const
		{
			return Determinant();
		}

		Vec<Vec2Data<Type> > operator*(Vec<Vec2Data<Type> > const &v) const;

		static Mat<Mat2Data<Type> > identity;
		static Mat<Mat2Data<Type> > empty;
		static Mat<Mat2Data<Type> > zeros;
		static Mat<Mat2Data<Type> > ones;
	};

	template <typename Type>
	Mat<Mat2Data<Type> > Mat2Data<Type>::Inverse() const
	{
		float d = Determinant();

		/* FIXME: should we actually do something here, exception? */
		if (d == 0.0)
			return *static_cast<Mat<Mat2Data<Type> > const *>(this);

		Mat<Mat2Data<Type> > copy;

		float *o = copy.values;
		float const *v = values;
		float s = 1.0 / d;

		o[0] = v[3] * s;
		o[1] = -v[1] * s;

		o[2] = -v[3] * s;
		o[3] = v[0] * s;

		return copy;
	}

	template <typename Type>
	Mat<Mat2Data<Type> > &Mat2Data<Type>::Invert()
	{
		Mat<Mat2Data<Type> > copy = Inverse();
		*this = copy;

		return *reinterpret_cast<Mat<Mat2Data<Type> > *>(this);
	}

	template <typename Type>
	Type Mat2Data<Type>::Determinant() const
	{
		float const *v = values;

		return v[0] * v[3] - v[2] * v[1];
	}

	template <typename Type>
	Mat<Mat2Data<Type> > Mat2Data<Type>::operator*(Mat2Data<Type> const &other) const
	{
		float const *a = values;
		float const *b = other.values;

		Type v[4] = {
			a[0] * b[0] + a[2] * b[1],
			a[1] * b[0] + a[3] * b[1],

			a[0] * b[2] + a[2] * b[3],
			a[1] * b[2] + a[3] * b[3],
		};

		return *reinterpret_cast<Mat<Mat2Data<Type> > *>(v);
	}

	template <typename Type>
	Vec<Vec2Data<Type> > Mat2Data<Type>::operator*(Vec<Vec2Data<Type> > const &v) const
	{
		float const *a = values;

		Type r[2] = {
			a[0] * v.x + a[2] * v.y,
			a[1] * v.x + a[3] * v.y
		};

		return *reinterpret_cast<Vec<Vec2Data<Type> > *>(r);
	}

	template <typename Type>
	struct Mat2 : Mat<Mat2Data<Type> >
	{
	};

	template <typename Type>
	struct mat2 : Mat2<Type>
	{
		mat2()
		{
		}

		mat2(Vec<Vec2Data<Type> > const &x, Vec<Vec2Data<Type> > const &y)
		{
			Mat2Data<Type>::x = static_cast<Vec2<Type> const &>(x);
			Mat2Data<Type>::y = static_cast<Vec2<Type> const &>(y);
		}

		mat2(Type const (&vals)[4])
		:
			Mat2<Type>(reinterpret_cast<Mat2<Type> const &>(vals))
		{
		}

		mat2(Mat2Data<Type> const &other)
		:
			Mat2<Type>(static_cast<Mat2<Type> const &>(other))
		{
		}
	};

	template <typename Type>
	Mat<Mat2Data<Type> > Mat2Data<Type>::identity = mat2<Type>(vec2<Type>(1, 0),
															   vec2<Type>(0, 1));

	template <typename Type>
	Mat<Mat2Data<Type> > Mat2Data<Type>::empty = mat2<Type>(vec2<Type>::empty,
														    vec2<Type>::empty);
	template <typename Type>
	Mat<Mat2Data<Type> > Mat2Data<Type>::zeros = Mat2Data<Type>::empty;

	template <typename Type>
	Mat<Mat2Data<Type> > Mat2Data<Type>::ones = mat2<Type>(vec2<Type>::ones,
														   vec2<Type>::ones);


	template <typename Type>
	struct Mat4Data;

	template <typename Type>
	struct Mat3Data : MatTypeDefine<Type, 3>
	{
		typedef Operators<Mat<Mat3Data<Type> > > Operator;

		union
		{
			Type values[9];

			struct
			{
				Vec<Vec3Data<Type> > x;
				Vec<Vec3Data<Type> > y;
				Vec<Vec3Data<Type> > z;
			};
		};

		Mat<Mat3Data<Type> > operator*(Mat3Data<Type> const &other) const;
		Mat<Mat3Data<Type> > operator*(Type single) const
		{
			return Operator::Operate(static_cast<Mat<Mat3Data<Type> > const &>(*this), single, Operator::Multiplier);
		}

		Mat<Mat3Data<Type> > Inverse() const;
		Mat<Mat3Data<Type> > &Invert();

		Type Determinant() const;
		Type Det() const
		{
			return Determinant();
		}

		Vec<Vec3Data<Type> > operator*(Vec<Vec3Data<Type> > const &v) const;
		Mat<Mat4Data<Type> > Extend() const;

		static Mat<Mat3Data<Type> > identity;
		static Mat<Mat3Data<Type> > empty;
		static Mat<Mat3Data<Type> > zeros;
		static Mat<Mat3Data<Type> > ones;

		static Mat<Mat3Data<Type> > Rotation(float angle, Vec<Vec3Data<Type> > const &axis);
	};

	template <typename Type>
	Mat<Mat4Data<Type> > Mat3Data<Type>::Extend() const
	{
		Type r[16] = {
			x.x, x.y, x.z, 0,
			y.x, y.y, y.z, 0,
			z.x, z.y, z.z, 0,
			0, 0, 0, 1
		};

		return *reinterpret_cast<Mat<Mat4Data<Type> > *>(r);
	}

	template <typename Type>
	Mat<Mat3Data<Type> > Mat3Data<Type>::Rotation(float angle, Vec<Vec3Data<Type> > const &axis)
	{
		Mat<Mat3Data<Type> > rot;

		float cosAngle = cos(angle);
		float sinAngle = sin(angle);

		float onec = 1.0 - cosAngle;

		rot.x = vec3<Type>(cosAngle, axis.z * sinAngle, -axis.y * sinAngle) + axis * onec * axis.x;
		rot.y = vec3<Type>(-axis.z * sinAngle, cosAngle, axis.x * sinAngle) + axis * onec * axis.y;
		rot.z = vec3<Type>(axis.y * sinAngle, -axis.x * sinAngle, cosAngle) + axis * onec * axis.z;

		return rot;
	}

	template <typename Type>
	Mat<Mat3Data<Type> > Mat3Data<Type>::Inverse() const
	{
		float d = Determinant();

		/* FIXME: should we actually do something here, exception? */
		if (d == 0.0)
			return *static_cast<Mat<Mat3Data<Type> > const *>(this);

		Mat<Mat3Data<Type> > copy;

		float *o = copy.values;
		float const *v = values;
		float s = 1.0 / d;

		o[0] = (v[4] * v[8] - v[7] * v[5]) * s;
		o[1] = (v[7] * v[2] - v[1] * v[8]) * s;
		o[2] = (v[1] * v[5] - v[4] * v[2]) * s;

		o[3] = (v[6] * v[5] - v[3] * v[8]) * s;
		o[4] = (v[0] * v[8] - v[6] * v[2]) * s;
		o[5] = (v[3] * v[2] - v[0] * v[5]) * s;

		o[6] = (v[3] * v[7] - v[6] * v[4]) * s;
		o[7] = (v[6] * v[1] - v[0] * v[7]) * s;
		o[8] = (v[0] * v[4] - v[3] * v[1]) * s;

		return copy;
	}

	template <typename Type>
	Mat<Mat3Data<Type> > &Mat3Data<Type>::Invert()
	{
		Mat<Mat3Data<Type> > copy = Inverse();
		*this = copy;

		return *reinterpret_cast<Mat<Mat3Data<Type> > *>(this);
	}

	template <typename Type>
	Type Mat3Data<Type>::Determinant() const
	{
		float const *v = values;

		return v[0] * v[4] * v[8] -
			   v[0] * v[5] * v[7] +
			   v[3] * v[7] * v[2] -
			   v[3] * v[8] * v[1] +
			   v[6] * v[1] * v[5] -
			   v[6] * v[2] * v[4];
	}

	template <typename Type>
	Mat<Mat3Data<Type> > Mat3Data<Type>::operator*(Mat3Data<Type> const &other) const
	{
		float const *a = values;
		float const *b = other.values;

		Type v[9] = {
			a[0] * b[0] + a[3] * b[1] + a[6] * b[2],
			a[1] * b[0] + a[4] * b[1] + a[7] * b[2],
			a[2] * b[0] + a[5] * b[1] + a[8] * b[2],

			a[0] * b[3] + a[3] * b[4] + a[6] * b[5],
			a[1] * b[3] + a[4] * b[4] + a[7] * b[5],
			a[2] * b[3] + a[5] * b[4] + a[8] * b[5],

			a[0] * b[6] + a[3] * b[7] + a[6] * b[8],
			a[1] * b[6] + a[4] * b[7] + a[7] * b[8],
			a[2] * b[6] + a[5] * b[7] + a[8] * b[8]
		};

		return *reinterpret_cast<Mat<Mat3Data<Type> > *>(v);
	}

	template <typename Type>
	Vec<Vec3Data<Type> > Mat3Data<Type>::operator*(Vec<Vec3Data<Type> > const &v) const
	{
		float const *a = values;

		float r[3] = {
			a[0] * v.x + a[3] * v.y + a[6] * v.z,
			a[1] * v.x + a[4] * v.y + a[7] * v.z,
			a[2] * v.x + a[5] * v.y + a[8] * v.z
		};

		return *reinterpret_cast<Vec<Vec3Data<Type> > *>(r);
	}

	template <typename Type>
	struct Mat3 : Mat<Mat3Data<Type> >
	{
	};

	template <typename Type>
	struct mat3 : Mat3<Type>
	{
		mat3()
		{
		}

		mat3(Vec<Vec3Data<Type> > const &x, Vec<Vec3Data<Type> > const &y, Vec<Vec3Data<Type> > const &z)
		{
			Mat3Data<Type>::x = static_cast<Vec3<Type> const &>(x);
			Mat3Data<Type>::y = static_cast<Vec3<Type> const &>(y);
			Mat3Data<Type>::z = static_cast<Vec3<Type> const &>(z);
		}

		mat3(Type const (&vals)[9])
		:
			Mat3<Type>(reinterpret_cast<Mat3<Type> const &>(vals))
		{
		}

		mat3(Mat3Data<Type> const &other)
		:
			Mat3<Type>(static_cast<Mat3<Type> const &>(other))
		{
		}
	};

	template <typename Type>
	Mat<Mat3Data<Type> > Mat3Data<Type>::identity = mat3<Type>(vec3<Type>(1, 0, 0),
															   vec3<Type>(0, 1, 0),
															   vec3<Type>(0, 0, 1));

	template <typename Type>
	Mat<Mat3Data<Type> > Mat3Data<Type>::empty = mat3<Type>(vec3<Type>::empty,
														    vec3<Type>::empty,
														    vec3<Type>::empty);
	template <typename Type>
	Mat<Mat3Data<Type> > Mat3Data<Type>::zeros = Mat3Data<Type>::empty;

	template <typename Type>
	Mat<Mat3Data<Type> > Mat3Data<Type>::ones = mat3<Type>(vec3<Type>::ones,
														   vec3<Type>::ones,
														   vec3<Type>::ones);

	template <typename Type>
	struct Mat4Data : MatTypeDefine<Type, 4>
	{
		typedef Operators<Mat<Mat4Data<Type> > > Operator;

		union
		{
			Type values[16];

			struct
			{
				Vec<Vec4Data<Type> > x;
				Vec<Vec4Data<Type> > y;
				Vec<Vec4Data<Type> > z;
				Vec<Vec4Data<Type> > w;
			};
		};

		Mat<Mat4Data<Type> > operator*(Mat4Data<Type> const &other) const;

		Mat<Mat4Data<Type> > operator*(Type single) const
		{
			return Operator::Operate(static_cast<Mat<Mat4Data<Type> > const &>(*this), single, Operator::Multiplier);
		}

		Mat<Mat4Data<Type> > Inverse() const;
		Mat<Mat4Data<Type> > &Invert();

		Type Determinant() const;
		Type Det() const
		{
			return Determinant();
		}

		Vec<Vec4Data<Type> > operator*(Vec<Vec4Data<Type> > const &v) const;

		static Mat<Mat4Data<Type> > identity;
		static Mat<Mat4Data<Type> > empty;
		static Mat<Mat4Data<Type> > zeros;
		static Mat<Mat4Data<Type> > ones;

		static Mat<Mat4Data<Type> > Rotation(float angle, Vec<Vec3Data<Type> > const &axis);
	};

	template <typename Type>
	Mat<Mat4Data<Type> > Mat4Data<Type>::Rotation(float angle, Vec<Vec3Data<Type> > const &axis)
	{
		return Mat<Mat3Data<Type> >::Rotation(angle, axis).extend();
	}

	template <typename Type>
	Mat<Mat4Data<Type> > Mat4Data<Type>::Inverse() const
	{
		float d = Determinant();

		/* FIXME: should we actually do something here, exception? */
		if (d == 0.0)
			return *static_cast<Mat<Mat4Data<Type> > const *>(this);

		Mat<Mat4Data<Type> > copy;

		float *o = copy.values;
		float const *v = values;
		float s = 1.0 / d;

		o[0] =  (v[9]  * v[14] * v[7]  - v[13] * v[10] * v[7]  + v[13] * v[6]  * v[11] -
		         v[5]  * v[14] * v[11] - v[9]  * v[6]  * v[15] + v[5]  * v[10] * v[15]) * s;
		o[1] =  (v[13] * v[10] * v[3]  - v[9]  * v[14] * v[3]  - v[13] * v[2]  * v[11] +
		         v[1]  * v[14] * v[11] + v[9]  * v[2]  * v[15] - v[1]  * v[10] * v[15]) * s;
		o[2] =  (v[5]  * v[14] * v[3]  - v[13] * v[6]  * v[3]  + v[13] * v[2]  * v[7]  -
		         v[1]  * v[14] * v[7]  - v[5]  * v[2]  * v[15] + v[1]  * v[6]  * v[15]) * s;
		o[3] =  (v[9]  * v[6]  * v[3]  - v[5]  * v[10] * v[3]  - v[9]  * v[2]  * v[7]  +
		         v[1]  * v[10] * v[7]  + v[5]  * v[2]  * v[11] - v[1]  * v[6]  * v[11]) * s;

		o[4] =  (v[12] * v[10] * v[7]  - v[8]  * v[14] * v[7]  - v[12] * v[6]  * v[11] +
		         v[4]  * v[14] * v[11] + v[8]  * v[6]  * v[15] - v[4]  * v[10] * v[15]) * s;
		o[5] =  (v[8]  * v[14] * v[3]  - v[12] * v[10] * v[3]  + v[12] * v[2]  * v[11] -
		         v[0]  * v[14] * v[11] - v[8]  * v[2]  * v[15] + v[0]  * v[10] * v[15]) * s;
		o[6] =  (v[12] * v[6]  * v[3]  - v[4]  * v[14] * v[3]  - v[12] * v[2]  * v[7]  +
		         v[0]  * v[14] * v[7]  + v[4]  * v[2]  * v[15] - v[0]  * v[6]  * v[15]) * s;
		o[7] =  (v[4]  * v[10] * v[3]  - v[8]  * v[6]  * v[3]  + v[8]  * v[2]  * v[7]  -
		         v[0]  * v[10] * v[7]  - v[4]  * v[2]  * v[11] + v[0]  * v[6]  * v[11]) * s;

		o[8] =  (v[8]  * v[13] * v[7]  - v[12] * v[9]  * v[7]  + v[12] * v[5]  * v[11] -
		         v[4]  * v[13] * v[11] - v[8]  * v[5]  * v[15] + v[4]  * v[9]  * v[15]) * s;
		o[9] =  (v[12] * v[9]  * v[3]  - v[8]  * v[13] * v[3]  - v[12] * v[1]  * v[11] +
		         v[0]  * v[13] * v[11] + v[8]  * v[1]  * v[15] - v[0]  * v[9]  * v[15]) * s;
		o[10] = (v[4]  * v[13] * v[3]  - v[12] * v[5]  * v[3]  + v[12] * v[1]  * v[7]  -
		         v[0]  * v[13] * v[7]  - v[4]  * v[1]  * v[15] + v[0]  * v[5]  * v[15]) * s;
		o[11] = (v[8]  * v[5]  * v[3]  - v[4]  * v[9]  * v[3]  - v[8]  * v[1]  * v[7]  +
		         v[0]  * v[9]  * v[7]  + v[4]  * v[1]  * v[11] - v[0]  * v[5]  * v[11]) * s;

		o[12] = (v[12] * v[9]  * v[6]  - v[8]  * v[13] * v[6]  - v[12] * v[5]  * v[10] +
		         v[4]  * v[13] * v[10] + v[8]  * v[5]  * v[14] - v[4]  * v[9]  * v[14]) * s;
		o[13] = (v[8]  * v[13] * v[2]  - v[12] * v[9]  * v[2]  + v[12] * v[1]  * v[10] -
		         v[0]  * v[13] * v[10] - v[8]  * v[1]  * v[14] + v[0]  * v[9]  * v[14]) * s;
		o[14] = (v[12] * v[5]  * v[2]  - v[4]  * v[13] * v[2]  - v[12] * v[1]  * v[6]   +
		         v[0]  * v[13] * v[6]  + v[4]  * v[1]  * v[14] - v[0]  * v[5]  * v[14]) * s;
		o[15] = (v[4]  * v[9]  * v[2]  - v[8]  * v[5]  * v[2]  + v[8]  * v[1]  * v[6]  -
		         v[0]  * v[9]  * v[6]  - v[4]  * v[1]  * v[10] + v[0]  * v[5]  * v[10]) * s;

		return copy;
	}

	template <typename Type>
	Mat<Mat4Data<Type> > &Mat4Data<Type>::Invert()
	{
		Mat<Mat4Data<Type> > copy = Inverse();
		*this = copy;

		return *reinterpret_cast<Mat<Mat4Data<Type> > *>(this);
	}

	template <typename Type>
	Type Mat4Data<Type>::Determinant() const
	{
		float const *v = values;

		return v[12] * v[9]  * v[6]  * v[3]  - v[8] * v[13] * v[6]  * v[3]  - v[12] * v[5] * v[10] * v[3]  +
		       v[4]  * v[13] * v[10] * v[3]  + v[8] * v[5]  * v[14] * v[3]  - v[4]  * v[9] * v[14] * v[3]  -
		       v[12] * v[9]  * v[2]  * v[7]  + v[8] * v[13] * v[2]  * v[7]  + v[12] * v[1] * v[10] * v[7]  -
		       v[0]  * v[13] * v[10] * v[7]  - v[8] * v[1]  * v[14] * v[7]  + v[0]  * v[9] * v[14] * v[7]  +
			   v[12] * v[5]  * v[2]  * v[11] - v[4] * v[13] * v[2]  * v[11] - v[12] * v[1] * v[6]  * v[11] +
			   v[0]  * v[13] * v[6]  * v[11] + v[4] * v[1]  * v[14] * v[11] - v[0]  * v[5] * v[14] * v[11] -
			   v[8]  * v[5]  * v[2]  * v[15] + v[4] * v[9]  * v[2]  * v[15] + v[8]  * v[1] * v[6]  * v[15] -
			   v[0]  * v[9]  * v[6]  * v[15] - v[4] * v[1]  * v[10] * v[15] + v[0]  * v[5] * v[10] * v[15];
	}

	template <typename Type>
	Mat<Mat4Data<Type> > Mat4Data<Type>::operator*(Mat4Data<Type> const &other) const
	{
		float const *a = values;
		float const *b = other.values;

		Type v[16] = {
			a[0] * b[0] + a[4] * b[1] + a[8] * b[2] + a[12] * b[3],
			a[1] * b[0] + a[5] * b[1] + a[9] * b[2] + a[13] * b[3],
			a[2] * b[0] + a[6] * b[1] + a[10] * b[2] + a[14] * b[3],
			a[3] * b[0] + a[7] * b[1] + a[11] * b[2] + a[15] * b[3],

			a[0] * b[4] + a[4] * b[5] + a[8] * b[6] + a[12] * b[7],
			a[1] * b[4] + a[5] * b[5] + a[9] * b[6] + a[13] * b[7],
			a[2] * b[4] + a[6] * b[5] + a[10] * b[6] + a[14] * b[7],
			a[3] * b[4] + a[7] * b[5] + a[11] * b[6] + a[15] * b[7],

			a[0] * b[8] + a[4] * b[9] + a[8] * b[10] + a[12] * b[11],
			a[1] * b[8] + a[5] * b[9] + a[9] * b[10] + a[13] * b[11],
			a[2] * b[8] + a[6] * b[9] + a[10] * b[10] + a[14] * b[11],
			a[3] * b[8] + a[7] * b[9] + a[11] * b[10] + a[15] * b[11],

			a[0] * b[12] + a[4] * b[13] + a[8] * b[14] + a[12] * b[15],
			a[1] * b[12] + a[5] * b[13] + a[9] * b[14] + a[13] * b[15],
			a[2] * b[12] + a[6] * b[13] + a[10] * b[14] + a[14] * b[15],
			a[3] * b[12] + a[7] * b[13] + a[11] * b[14] + a[15] * b[15],
		};

		return *reinterpret_cast<Mat<Mat4Data<Type> > *>(v);
	}

	template <typename Type>
	Vec<Vec4Data<Type> > Mat4Data<Type>::operator*(Vec<Vec4Data<Type> > const &v) const
	{
		float const *a = values;

		float r[4] = {
			a[0] * v.x + a[4] * v.y + a[8] * v.z + a[12] * v.w,
			a[1] * v.x + a[5] * v.y + a[9] * v.z + a[13] * v.w,
			a[2] * v.x + a[6] * v.y + a[10] * v.z + a[14] * v.w,
			a[3] * v.x + a[7] * v.y + a[11] * v.z + a[15] * v.w
		};

		return *reinterpret_cast<Vec<Vec4Data<Type> > *>(r);
	}

	template <typename Type>
	struct Mat4 : Mat<Mat4Data<Type> >
	{
	};

	template <typename Type>
	struct mat4 : Mat4<Type>
	{
		mat4()
		{
		}

		mat4(Vec<Vec4Data<Type> > const &x, Vec<Vec4Data<Type> > const &y, Vec<Vec4Data<Type> > const &z, Vec<Vec4Data<Type> > const &w)
		{
			Mat4Data<Type>::x = static_cast<Vec4<Type> const &>(x);
			Mat4Data<Type>::y = static_cast<Vec4<Type> const &>(y);
			Mat4Data<Type>::z = static_cast<Vec4<Type> const &>(z);
			Mat4Data<Type>::w = static_cast<Vec4<Type> const &>(w);
		}

		mat4(Type const (&vals)[16])
		:
			Mat4<Type>(reinterpret_cast<Mat4<Type> const &>(vals))
		{
		}

		mat4(Mat4Data<Type> const &other)
		:
			Mat4<Type>(static_cast<Mat4<Type> const &>(other))
		{
		}
	};

	template <typename Type>
	Mat<Mat4Data<Type> > Mat4Data<Type>::identity = mat4<Type>(vec4<Type>(1, 0, 0, 0),
															   vec4<Type>(0, 1, 0, 0),
															   vec4<Type>(0, 0, 1, 0),
															   vec4<Type>(0, 0, 0, 1));

	template <typename Type>
	Mat<Mat4Data<Type> > Mat4Data<Type>::empty = mat4<Type>(vec4<Type>::empty,
														    vec4<Type>::empty,
														    vec4<Type>::empty,
														    vec4<Type>::empty);
	template <typename Type>
	Mat<Mat4Data<Type> > Mat4Data<Type>::zeros = Mat4Data<Type>::empty;

	template <typename Type>
	Mat<Mat4Data<Type> > Mat4Data<Type>::ones = mat4<Type>(vec4<Type>::ones,
														   vec4<Type>::ones,
														   vec4<Type>::ones,
														   vec4<Type>::ones);

}
}

#endif /* __JESSEVDK_MATH_MAT_H__ */
