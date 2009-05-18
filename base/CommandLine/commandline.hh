#ifndef __BASE_COMMAND_LINE_H__
#define __BASE_COMMAND_LINE_H__

#include <string>

namespace base
{
	
	/** Class for parsing command line arguments.
	  * This class is a convenient wrapper around getopt.
	  * @author Jesse van den Kieboom
	  */
	class CommandLine
	{
		static CommandLine *s_instance;

		std::string d_basename;
		size_t d_nOptions;
		std::string d_option;
		size_t *d_numOptions;
		std::string *d_options;

		size_t d_nArguments;
		std::string *d_arguments;

		public:
			/** Intialize command line singleton instance.
			  * This initializes the command line singleton instance. The
			  * arguments provided to your main() function should be provided
			  * to this initialization to let the class parse the arguments.
			  * @param argc the number of arguments in @argv
			  * @param argv the command line arguments
			  * @param optstr a getopt option string to specify possible options
			  * @return the command line singleton instance
			  * @author Jesse van den Kieboom
			  */
			static CommandLine &initialize(int argc, char * const *argv, char const *optstr);

			/** Get the command line singleton instance.
			  * This returns the command line singleton instance. If the
			  * instance is not yet initialized with @initialize, then a runtime
			  * exception is thrown
			  * @return the command line singleton instance
			  * @author Jesse van den Kieboom
			  */
			static CommandLine &instance();

			/** Get command line argument.
			  * This function can be used to get command line arguments still
			  * left after the command arguments have been processed
			  * @param num the index of the argument to get
			  * @return the argument
			  * @author Jesse van den Kieboom
			  */
			char const *argument(size_t num) const;

			/** Get the application basename.
			  * This returns the application basename which should have
			  * been supplied by argv[0] in the initialization
			  * @return the application basename
			  * @author Jesse van den Kieboom
			  */
			std::string const &basename() const;

			/** Get number of arguments.
			  * This returns the number of arguments left after the command
			  * line arguments have been processed
			  * @return the number of arguments
			  * @author Jesse van den Kieboom
			  */
			size_t nArguments() const; // Accessor for d_nArguments

			/** Get number of options.
			  * This returns the number of options specified in the option
			  * string at initialization
			  * @return the number of options
			  * @author Jesse van den Kieboom
			  */
			size_t nOptions() const; // Accessor for d_nOptions
			
			/** Get number of times an option was specified.
			  * This function returns the number of options specified on
			  * the command line
			  * @param opt the option to return the number for (e.g. 'v')
			  * @return the number of times @opt was specified
			  * @author Jesse van den Kieboom
			  */
			size_t option(int opt) const;

			/** Get whether or not certain options were specified.
			  * This function returns whether or any of the specified 
			  * options were specified on the command line
			  * @param opts the options to check
			  * @return true if any options in @opts were specified, false
			  * otherwise
			  * @author Jesse van den Kieboom
			  */
			bool option(char const *opts) const;

			/** Get an option argument.
			  * This function gets an option argument for a certain option.
			  * The argument (if there was any) will be put in @value
			  * @param value the location where the argument value will be put
			  * @param opt the option to get the argument value for
			  * @return true if the option could be found and has an argument
			  * value, false otherwise
			  * @author Jesse van den Kieboom
			  */
			bool option(std::string *value, int opt) const;
		private:
			CommandLine(CommandLine const &other); // NI
			CommandLine(int argc, char * const *argv, char const *optstr);

			void parseNumOptions(char const *optstr);
			int parseOptions(int argc, char * const *argv, 
					 char const *optstr);
			void parseArguments(char * const *start, 
					    char * const *end);
			int optionIndex(int opt) const;
	};
	
	inline size_t CommandLine::nArguments() const
	{
		return d_nArguments;
	}
	
	inline size_t CommandLine::nOptions() const
	{
		return d_nOptions;
	}
	
	inline std::string const &CommandLine::basename() const
	{
		return d_basename;
	}	
}

#endif /* __BASE_COMMAND_LINE__ */
