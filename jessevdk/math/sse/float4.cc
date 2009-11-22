#include "float4.hh"

#ifdef ENABLE_SSE
math::sse::Implementation *math::Vec<Vec4Data<float> >::s_implementation = 0;
#endif
