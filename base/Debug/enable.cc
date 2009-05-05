#include "debug.ih"

void Debug::enable(int domain) 
{
	if (!s_instance)
		s_instance = new Debug();
	
	s_instance->domain() |= domain;
}
