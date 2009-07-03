#ifndef __MATH_SSE_IMPLEMENTATION_H__
#define __MATH_SSE_IMPLEMENTATION_H__

#include <math/vec.hh>

namespace math
{
namespace sse
{
	class Implementation
	{
		public:
			static Implementation *s_implementation;
			
			virtual ~Implementation() {};

			virtual float sum(Vec<Vec4Data<float> > const &v) = 0;

			virtual float index(Vec<Vec4Data<float> > const &v, size_t idx) = 0;
			virtual float &index(Vec<Vec4Data<float> > &v, size_t idx) = 0;

			virtual Vec<Vec4Data<float> > add(Vec<Vec4Data<float> > const &v, float single) = 0;
			virtual Vec<Vec4Data<float> > add(Vec<Vec4Data<float> > const &v, Vec<Vec4Data<float> > const &other) = 0;
			virtual Vec<Vec4Data<float> > &add(Vec<Vec4Data<float> > &v, float single) = 0;
			virtual Vec<Vec4Data<float> > &add(Vec<Vec4Data<float> > &v, Vec<Vec4Data<float> > const &other) = 0;
			
			virtual Vec<Vec4Data<float> > substract(Vec<Vec4Data<float> > const &v, float single) = 0;
			virtual Vec<Vec4Data<float> > substract(Vec<Vec4Data<float> > const &v, Vec<Vec4Data<float> > const &other) = 0;
			virtual Vec<Vec4Data<float> > &substract(Vec<Vec4Data<float> > &v, float single) = 0;
			virtual Vec<Vec4Data<float> > &substract(Vec<Vec4Data<float> > &v, Vec<Vec4Data<float> > const &other) = 0;

			virtual Vec<Vec4Data<float> > multiply(Vec<Vec4Data<float> > const &v, float single) = 0;
			virtual Vec<Vec4Data<float> > multiply(Vec<Vec4Data<float> > const &v, Vec<Vec4Data<float> > const &other) = 0;
			virtual Vec<Vec4Data<float> > &multiply(Vec<Vec4Data<float> > &v, float single) = 0;
			virtual Vec<Vec4Data<float> > &multiply(Vec<Vec4Data<float> > &v, Vec<Vec4Data<float> > const &other) = 0;

			virtual Vec<Vec4Data<float> > divide(Vec<Vec4Data<float> > const &v, float single) = 0;
			virtual Vec<Vec4Data<float> > divide(Vec<Vec4Data<float> > const &v, Vec<Vec4Data<float> > const &other) = 0;
			virtual Vec<Vec4Data<float> > &divide(Vec<Vec4Data<float> > &v, float single) = 0;
			virtual Vec<Vec4Data<float> > &divide(Vec<Vec4Data<float> > &v, Vec<Vec4Data<float> > const &other) = 0;

			virtual float length(Vec<Vec4Data<float> > const &v) = 0;

			virtual Vec<Vec4Data<float> > normalize(Vec<Vec4Data<float> > const &v) = 0;
			virtual Vec<Vec4Data<float> > &normalize(Vec<Vec4Data<float> > &v) = 0;
			
			virtual Vec<Vec4Data<float> > invert(Vec<Vec4Data<float> > const &v) = 0;
			virtual Vec<Vec4Data<float> > &invert(Vec<Vec4Data<float> > &v) = 0;
		
			virtual float dot(Vec<Vec4Data<float> > const &v, Vec<Vec4Data<float> > const &other) = 0;
	};
}

}

#endif /* __MATH_SSE_IMPLEMENTATION_H__ */

