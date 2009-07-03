#include "commandline.ih"

bool CommandLine::option(char const *opts) const
{
	while (*opts)
	{
		if (optionIndex(*opts) != -1)
			return true;
		
		++opts;
	}
	
	return false;
}
