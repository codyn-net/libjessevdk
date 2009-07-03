#include "environment.ih"

bool Environment::variable(string const &name) 
{
	return getenv(name.c_str()) != 0;
}
