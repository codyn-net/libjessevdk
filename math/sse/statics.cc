#include "float4.ih"

#ifdef ENABLE_SSE
sse::Implementation *Vec<Vec4Data<float> >::s_implementation = 0;
#endif
