#include "filesystem.ih"

string FileSystem::uniqueName(string const &filename) 
{
	string path;
	
	if (!realpath(filename, path))
		return filename;
	
	size_t i = 1;
	string original = path;
	
	while (fileExists(path))
	{
		stringstream s;
		s << original << "." << i;

		path = s.str();
	}
	
	return path;
}
