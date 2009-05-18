#include "commandline.ih"

void CommandLine::parseArguments(char * const *start, char * const *end)
{
	d_nArguments = end - start;
	d_arguments = new string[d_nArguments];
	
	for (char * const *item = start; item != end; ++item)
		d_arguments[item - start] = *item;
}
