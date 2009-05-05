#include "module.ih"

bool Module::open() 
{
	if (d_data->path == "")
	{
		d_data->error = "File does not exist";
		return false;
	}
	
	d_data->handle = dlopen(d_data->path.c_str(), RTLD_LAZY | RTLD_GLOBAL);
	
	if (!d_data->handle)
	{
		d_data->error = dlerror();
		return false;
	}
	
	return true;
}
