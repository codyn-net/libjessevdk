#include "commandline.ih"

CommandLine &CommandLine::initialize(int argc, char * const *argv, char const *optstr)
{
	if (s_instance)
	{
		cerr << "Can't reinitialize arguments" << endl;
		exit(1); // BS, okay for now?
	}
	
	return *(s_instance = new CommandLine(argc, argv, optstr));
}
