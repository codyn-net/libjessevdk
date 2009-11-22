#ifndef __JESSEVDK_MATH_SSE_IMPLEMENTATION_H__
#define __JESSEVDK_MATH_SSE_IMPLEMENTATION_H__

#include <jessevdk/math/vec.hh>

namespace jessevdk
{
namespace math
{
namespace sse
{
	class Implementation
	{
		public:
			static Implementation *s_implementation;

			virtual ~Implementation() {};

			virtual float Sum(Vec<Vec4Data<float> > const &v) = 0;

			virtual float Index(Vec<Vec4Data<float> > const &v, size_t idx) = 0;
			virtual float &Index(Vec<Vec4Data<float> > &v, size_t idx) = 0;

			virtual Vec<Vec4Data<float> > Add(Vec<Vec4Data<float> > const &v, float single) = 0;
			virtual Vec<Vec4Data<float> > Add(Vec<Vec4Data<float> > const &v, Vec<Vec4Data<float> > const &other) = 0;
			virtual Vec<Vec4Data<float> > &Add(Vec<Vec4Data<float> > &v, float single) = 0;
			virtual Vec<Vec4Data<float> > &Add(Vec<Vec4Data<float> > &v, Vec<Vec4Data<float> > const &other) = 0;

			virtual Vec<Vec4Data<float> > Substract(Vec<Vec4Data<float> > const &v, float single) = 0;
			virtual Vec<Vec4Data<float> > Substract(Vec<Vec4Data<float> > const &v, Vec<Vec4Data<float> > const &other) = 0;
			virtual Vec<Vec4Data<float> > &Substract(Vec<Vec4Data<float> > &v, float single) = 0;
			virtual Vec<Vec4Data<float> > &Substract(Vec<Vec4Data<float> > &v, Vec<Vec4Data<float> > const &other) = 0;

			virtual Vec<Vec4Data<float> > Multiply(Vec<Vec4Data<float> > const &v, float single) = 0;
			virtual Vec<Vec4Data<float> > Multiply(Vec<Vec4Data<float> > const &v, Vec<Vec4Data<float> > const &other) = 0;
			virtual Vec<Vec4Data<float> > &Multiply(Vec<Vec4Data<float> > &v, float single) = 0;
			virtual Vec<Vec4Data<float> > &Multiply(Vec<Vec4Data<float> > &v, Vec<Vec4Data<float> > const &other) = 0;

			virtual Vec<Vec4Data<float> > Divide(Vec<Vec4Data<float> > const &v, float single) = 0;
			virtual Vec<Vec4Data<float> > Divide(Vec<Vec4Data<float> > const &v, Vec<Vec4Data<float> > const &other) = 0;
			virtual Vec<Vec4Data<float> > &Divide(Vec<Vec4Data<float> > &v, float single) = 0;
			virtual Vec<Vec4Data<float> > &Divide(Vec<Vec4Data<float> > &v, Vec<Vec4Data<float> > const &other) = 0;

			virtual float Length(Vec<Vec4Data<float> > const &v) = 0;

			virtual Vec<Vec4Data<float> > Normalize(Vec<Vec4Data<float> > const &v) = 0;
			virtual Vec<Vec4Data<float> > &Normalize(Vec<Vec4Data<float> > &v) = 0;

			virtual Vec<Vec4Data<float> > Invert(Vec<Vec4Data<float> > const &v) = 0;
			virtual Vec<Vec4Data<float> > &Invert(Vec<Vec4Data<float> > &v) = 0;

			virtual float Dot(Vec<Vec4Data<float> > const &v, Vec<Vec4Data<float> > const &other) = 0;
	};
}
}
}

#endif /* __JESSEVDK_MATH_SSE_IMPLEMENTATION_H__ */

