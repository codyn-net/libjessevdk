#include "addressinfo.ih"

AddressInfo::AddressInfo()
{
	d_data = new Data();
	addPrivateData(d_data);
	
	d_data->address = 0;
	d_data->current = 0;
	d_data->freeAddress = false;
}
