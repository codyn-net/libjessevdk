#include "commandline.ih"

int CommandLine::optionIndex(int opt) const
{
	// Find 'opt' in d_option
	string::size_type idx = d_option.find(opt);
	
	if (idx == string::npos)
		return -1;
	
	return idx;
}
