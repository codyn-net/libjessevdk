#include "commandline.ih"

char const *CommandLine::argument(size_t num) const
{
	return (num < 0 || num >= d_nArguments) ? 0 : d_arguments[num].c_str();		
}
