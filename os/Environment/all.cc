#include "environment.ih"
extern char **environ;

map<string, string> Environment::all() 
{
	char **ptr;
	map<string, string> ret;
	
	for (ptr = environ; ptr && *ptr; ++ptr)
	{
		vector<string> parts = String(*ptr).split("=", 2);
		
		if (parts.size() == 2)
		{
			ret[parts[0]] = parts[1];
		}
	}
	
	return ret;
}
