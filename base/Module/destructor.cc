#include "module.ih"

Module::~Module() 
{
	if (d_handle)
		dlclose(d_handle);
}
