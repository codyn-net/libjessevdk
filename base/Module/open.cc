#include "module.ih"

void Module::open() 
{
	if (!d_path)
	{
		d_error = "File does not exist";
		return;
	}
	
	d_handle = dlopen(d_path.c_str(), RTLD_LAZY | RTLD_GLOBAL);
	
	if (!d_handle)
	{
		d_error = dlerror();
		return false;
	}
	
	return true;
}
