#include "module.ih"

Module::Data::~Data() 
{
	if (state && handle)
		dlclose(handle);
}
