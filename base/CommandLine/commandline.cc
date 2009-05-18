#include "commandline.ih"
#include <libgen.h>

CommandLine::CommandLine(int argc, char * const *argv, char const *optstr)
:
	d_basename(::basename(argv[0]))
{
	// Parse options, returns the index where arguments start in argv 
	int argStart = parseOptions(argc, argv, optstr);

	// Parse all the arguments
	parseArguments(argv + argStart, argv + argc);
}
