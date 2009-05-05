#include "debug.ih"

void Debug::enableEnvironment() 
{
	if (!s_instance)
		s_instance = new Debug(cerr);
	
	if (Environment::variable("OPTIMIZATION_DEBUG_NETWORK"))
		s_instance->domain() |= Domain::Network;
	
	if (Environment::variable("OPTIMIZATION_DEBUG_WORKER"))
		s_instance->domain() |= Domain::Worker;
	
	if (Environment::variable("OPTIMIZATION_DEBUG_MODULE"))
		s_instance->domain() |= Domain::Module;
}
