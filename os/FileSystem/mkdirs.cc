#include "filesystem.ih"

bool FileSystem::mkdirs(string const &path) 
{
	vector<string> parts = String(path).split("/");
	string full;
	
	for (vector<string>::iterator iter = parts.begin(); iter != parts.end(); ++iter)
	{
		full = full + "/" + *iter;

		if (!directoryExists(full))
		{
			if (::mkdir(full.c_str(), 0755) != 0)
				return false;
		}
	}
	
	return true;
}
