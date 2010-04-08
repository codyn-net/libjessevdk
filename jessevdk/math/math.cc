#include "math.hh"

#ifdef ENABLE_SSE
#include <cpuid.h>
#endif

using namespace jessevdk::math;

Math::InverseSqrtfFunc Math::s_inverseSqrtf = &Math::InverseSqrtfDefault;
Math::InverseSqrtFunc Math::s_inverseSqrt = &Math::InverseSqrtDefault;

void
Math::Initialize(bool usesse)
{
	#ifdef ENABLE_SSE
	if (usesse)
	{
		unsigned int eax, ebx, ecx, edx;

		if (__get_cpuid(1, &eax, &ebx, &ecx, &edx) && (edx & bit_SSE))
		{
			Vec<Vec4Data<float> >::s_implementation = new sse::Float4ImplSSE();
			return;
		}
	}
	Vec<Vec4Data<float> >::s_implementation = new sse::Float4Impl();
	#endif
}


void
Math::SetInverseSqrtf(InverseSqrtfFunc func)
{
	s_inverseSqrtf = func;
}

void
Math::SetInverseSqrt(InverseSqrtFunc func)
{
	s_inverseSqrt = func;
}

float
Math::InverseSqrtfDefault(float x)
{
	return 1 / sqrtf(x);
}

float
Math::InverseSqrtfFast(float x)
{
	float xhalf = 0.5f * x;
	int i = *(int*)&x;

	i = 0x5f3759df - (i >> 1);
	x = *(float*)&i;

	x = x * (1.5f - xhalf * x * x);

	return x;
}

double
Math::InverseSqrtDefault(double x)
{
	return 1 / sqrt(x);
}

double
Math::InverseSqrtFast(double x)
{
	return InverseSqrtfFast(x);
}

