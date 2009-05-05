#include "module.ih"

Module::Module(string const &path)
{
	d_data = new Data();
	addPrivateData(d_data);

	d_data->path = resolvePath(path);
	d_data->state = open();
}
