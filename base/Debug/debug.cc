#include "debug.ih"

Debug::Debug(int domain) 
:
	d_stream(cout),
	d_nostream(new StreamBuf()),
	d_domain(domain)
{
}
