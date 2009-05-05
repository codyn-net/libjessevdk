#include "debug.ih"

void Debug::enableEnvironment(ostream &stream)
{
	if (s_instance)
		delete s_instance;
	
	s_instance = new Debug(stream);
	enableEnvironment();
}
