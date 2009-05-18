#include "commandline.ih"

size_t CommandLine::option(int opt) const
{
	int idx = optionIndex(opt);
	
	if (idx == -1)
		return 0;
	
	return d_numOptions[idx];
}
