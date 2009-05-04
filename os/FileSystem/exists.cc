#include "filesystem.ih"

bool FileSystem::exists(string const &filename) 
{
	return fileExists(filename) || directoryExists(filename);
}
