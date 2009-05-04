#include "filesystem.ih"

bool FileSystem::move(string const &from, string const &to) 
{	
	if (!copy(from, to))
		return false;
		
	// Remove `from`
	unlink(from.c_str());
	return true;
}
