#include "module.ih"

Module::Module() 
{
	d_data = new Data();
	addPrivateData(d_data);
	
	d_data->state = false;
	d_data->handle = 0;
}
