#include "environment.hh"

#include <stdlib.h>
#include <unistd.h>
#include <jessevdk/base/string.hh>

using namespace std;
using namespace jessevdk::os;
using namespace jessevdk::base;
extern char **environ;

map<string, string>
Environment::All()
{
	char **ptr;
	map<string, string> ret;

	for (ptr = environ; ptr && *ptr; ++ptr)
	{
		vector<string> parts = String(*ptr).Split("=", 2);

		if (parts.size() == 2)
		{
			ret[parts[0]] = parts[1];
		}
	}

	return ret;
}

vector<string>
Environment::Convert(map<string, string> const &environment)
{
	map<string, string>::const_iterator iter;
	vector<string> ret;

	for (iter = environment.begin(); iter != environment.end(); ++iter)
	{
		ret.push_back(iter->first + "=" + iter->second);
	}

	return ret;
}

vector<string>
Environment::Path(string const &name)
{
	string p;
	vector<string> result;

	if (!Environment::Variable(name, p))
	{
		return result;
	}

	return String(p).Split(":");
}

bool
Environment::Variable(string const &name, string &variable)
{
	char *ptr = getenv(name.c_str());

	if (ptr)
	{
		variable = ptr;
	}

	return ptr != 0;
}

bool
Environment::Variable(string const &name)
{
	return getenv(name.c_str()) != 0;
}
