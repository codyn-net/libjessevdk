#include "environment.ih"

vector<string> Environment::convert(map<string, string> const &environment)
{
	map<string, string>::const_iterator iter;
	vector<string> ret;

	for (iter = environment.begin(); iter != environment.end(); ++iter)
	{
		ret.push_back(iter->first + "=" + iter->second);
	}
	
	return ret;
}
