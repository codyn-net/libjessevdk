#include "math.hh"

#ifdef ENABLE_SSE
#include <cpuid.h>
#endif

void
jessevdk::math::Initialize(bool usesse)
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
