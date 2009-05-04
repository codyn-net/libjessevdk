#include "filesystem.ih"

bool FileSystem::fileExists(string const &filename)
{
	struct stat buf;
	return (stat(filename.c_str(), &buf) == 0) && S_ISREG(buf.st_mode);
}
