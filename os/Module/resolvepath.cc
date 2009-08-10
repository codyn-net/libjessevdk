#include "module.ih"

string Module::resolvePath(string const &path) const
{
	String s(path);
	
	if (!s.endsWith(Module::suffix))
		s += Module::suffix;
	
	string res;
	return FileSystem::realpath(path, res) ? res : "";
}
