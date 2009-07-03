#include "commandline.ih"

void CommandLine::parseNumOptions(char const *optstr)
{
	d_nOptions = 0;
	
	while (*optstr)
		d_nOptions += (*optstr++ != ':');
}
