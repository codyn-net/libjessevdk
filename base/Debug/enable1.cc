#include "debug.ih"

void Debug::enable(ostream &stream, int domain) 
{
	if (s_instance)
		delete s_instance;
	
	s_instance = new Debug(stream, domain);
}
