#include "filesystem.ih"

bool FileSystem::resolveBinary(string const &filename, string &path)
{
	vector<string> paths = Environment::path("PATH");
	return FileSystem::find(paths, filename, path);
}
