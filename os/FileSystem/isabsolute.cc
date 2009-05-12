#include "filesystem.ih"

bool FileSystem::isAbsolute(string const &path) 
{
	return !path.empty() && path[0] == '/';
}
