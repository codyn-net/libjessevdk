#include "environment.ih"

vector<string> Environment::path(string const &name) 
{
	string p;
	vector<string> result;
	
	if (!Environment::variable(name, p))
		return result;
	
	return String(p).split(":");
}
