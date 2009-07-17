#include "addressinfo.ih"

AddressInfo::AddressInfo(int ret, struct addrinfo *addr)
{
	d_data = new Data();
	addPrivateData(d_data);
	
	d_data->freeAddress = false;

	if (ret != 0 || !addr)
	{
		d_data->address = 0;
		d_data->current = 0;
	}
	else
	{
		d_data->address = addr;
		d_data->current = addr;
	}
}
