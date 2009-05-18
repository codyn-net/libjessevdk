#ifndef __MATH_MATH_H__
#define __MATH_MATH_H__

#include <math/vec.hh>
#include <math/mat.hh>
#include <cmath>
#include <math/Random/random.hh>

#ifdef ENABLE_SSE
#include <math/sse/float4.hh>
#include <math/sse/float4impl.hh>
#include <math/sse/float4implsse.hh>
#endif

namespace math
{
	// simple type definitions for common vector types
	typedef vec2<float> float2;
	typedef vec3<float> float3;
	typedef vec4<float> float4;
	
	typedef vec2<int> int2;
	typedef vec3<int> int3;
	typedef vec4<int> int4;
	
	typedef mat2<float> float2x2;
	typedef mat3<float> float3x3;
	typedef mat4<float> float4x4;
	
	typedef mat2<int> int2x2;
	typedef mat3<int> int3x3;
	typedef mat4<int> int4x4;
	
	void initialize(bool usesse = true);

	template <typename T>
	T max(T const &a, T const &b)
	{
		return a > b ? a : b;
	}
	
	template <typename T>
	T min(T const &a, T const &b)
	{
		return a < b ? a : b;
	}
	
	template <typename Container>
	static typename Container::value_type euclidean(Container const &container)
	{
		typename Container::const_iterator iter;
		typename Container::value_type sum;
		
		for (iter = container.begin(); iter != container.end(); ++iter)
			sum += *iter * *iter;
		
		return ::sqrt(sum);
	}
}
#endif /* __MATH_MATH_H__ */
