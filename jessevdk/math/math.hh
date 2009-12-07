#ifndef __JESSEVDK_MATH_MATH_H__
#define __JESSEVDK_MATH_MATH_H__

#include <jessevdk/math/vec.hh>
#include <jessevdk/math/mat.hh>
#include <jessevdk/math/random.hh>
#include <cmath>
#include <jessevdk/config.hh>

#ifdef JESSEVDK_ENABLE_SSE
#include <jessevdk/math/sse/float4.hh>
#include <jessevdk/math/sse/float4impl.hh>
#include <jessevdk/math/sse/float4implsse.hh>
#endif

namespace jessevdk
{
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

	void Initialize(bool usesse = true);

	template <typename T>
	T Max(T const &a, T const &b)
	{
		return a > b ? a : b;
	}

	template <typename T>
	T Min(T const &a, T const &b)
	{
		return a < b ? a : b;
	}

	template <typename T>
	T Mix(T const &a, T const &b, float alpha)
	{
		return a + alpha * (b - a);
	}

	template <typename T>
	T Clip(T const &a, T const &b, T const &c)
	{
		return a < b ? b : (a > c ? c : a);
	}

	template <typename Container>
	static typename Container::value_type Euclidean(Container const &container)
	{
		typename Container::const_iterator iter;
		typename Container::value_type sum;

		for (iter = container.begin(); iter != container.end(); ++iter)
		{
			sum += *iter * *iter;
		}

		return ::sqrt(sum);
	}
}
}

#endif /* __JESSEVDK_MATH_MATH_H__ */
