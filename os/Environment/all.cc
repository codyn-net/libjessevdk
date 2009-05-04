#include "environment.ih"
extern char **environ;

vector<string> Environment::all() 
{
	char **ptr;
	vector<string> ret;
	
	for (ptr = environ; ptr && *ptr; ++ptr)
	{
		ret.push_back(*ptr);
	}
	
	return ret;
}
