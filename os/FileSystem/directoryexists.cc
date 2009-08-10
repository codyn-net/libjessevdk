#include "filesystem.ih"

bool FileSystem::directoryExists(string const &filename)
{
	struct stat buf;
	return (stat(filename.c_str(), &buf) == 0) && S_ISDIR(buf.st_mode);
}
