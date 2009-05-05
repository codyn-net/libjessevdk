#include "debug.ih"

Debug::Debug(ostream &stream, int domain)
:
	d_stream(stream),
	d_nostream(new StreamBuf()),
	d_domain(domain)
{
	
}
