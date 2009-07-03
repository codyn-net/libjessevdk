#include "filesystem.ih"

bool FileSystem::realpath(string const &path, string &real)
{
	char p[PATH_MAX];
	
	char *ptr = ::realpath(path.c_str(), p);
	
	if (!ptr)
		return false;
	
	real = ptr;
	return true;	
}
