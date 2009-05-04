#include "module.ih"

Module::Module(string const &path)
{
	d_path = resolvePath(path);
	d_state = open();
}
