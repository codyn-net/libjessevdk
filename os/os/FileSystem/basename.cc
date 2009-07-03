#include "filesystem.ih"

string FileSystem::basename(string const &filename) 
{
	char *buf = new char[filename.size() + 1];
	strcpy(buf, filename.c_str());

	char *copy = ::basename(buf);
	string result(copy);
	
	free(buf);
	return result;
}
