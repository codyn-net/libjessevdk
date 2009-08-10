#include "commandline.ih"

int CommandLine::parseOptions(int argc, char * const *argv, char const *optstr)
{
	// Calculate d_nOptions
	parseNumOptions(optstr);
	
	// Initialize to maximum number of options
	d_options = new string[d_nOptions];
	d_numOptions = new size_t[d_nOptions];
	
	size_t ocnt = 0;
	int opt;
	
	while ((opt = getopt(argc, argv, optstr)) != -1)
	{
		switch (opt)
		{
			case ':':
				cerr << "Missing option value" << endl;
				exit(EXIT_FAILURE);
			case '?':
				cerr << "Unknown option" << endl;
				exit(EXIT_FAILURE);
			default:
				int pos = optionIndex(opt);
				
				if (pos == -1)
				{
					// Option not yet present
					d_option += static_cast<char>(opt);
					d_numOptions[ocnt] = 0;
					pos = ocnt++;
				}
				
				if (optarg)
					d_options[pos] = optarg;

				d_numOptions[pos] = d_numOptions[pos] + 1;
		}
	}

	return optind;
}
