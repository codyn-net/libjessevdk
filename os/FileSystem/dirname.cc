#include "filesystem.ih"
#include <libgen.h>

string FileSystem::dirname(string const &filename) 
{
	char *buf = new char[filename.size() + 1];
	strcpy(buf, filename.c_str());

	char *copy = ::dirname(buf);
	string result(copy);
	
	free(buf);
	return result;
}
