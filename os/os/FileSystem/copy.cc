#include "filesystem.ih"

bool FileSystem::copy(string const &from, string const &to) 
{
	if (!exists(from))
		return false;
	
	ifstream ifstr(from.c_str(), ios::in);
	ofstream ofstr(to.c_str(), ios::trunc | ios::out);
	
	return ofstr << ifstr.rdbuf();	
}
