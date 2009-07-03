#include "debug.ih"

bool Debug::enabled(int domain)
{
	return s_instance ? (s_instance->domain() & domain) : false;
}
