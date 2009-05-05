#include "debug.ih"

void Debug::disable(int domain) 
{
	if (!s_instance)
		s_instance = new Debug();
	
	s_instance->domain() &= ~domain;
}
