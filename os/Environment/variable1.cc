#include "environment.ih"

bool Environment::variable(string const &name, string &variable) 
{
	char *ptr = getenv(name.c_str());
	
	if (ptr)
		variable = ptr;
	
	return ptr != 0;		
}
