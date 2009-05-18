#include "commandline.ih"

bool CommandLine::option(std::string *value, int opt) const
{
	int idx = optionIndex(opt);
	
	if (idx == -1)
		return false;
	
	*value = d_options[idx];
	return true;
}
