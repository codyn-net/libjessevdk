#include "commandline.ih"

CommandLine &CommandLine::instance()
{
	if (!s_instance)
		throw runtime_error("CommandLine not yet initialized");
	
	return *s_instance;
}
