#include "addressinfo.ih"

void AddressInfo::initialize(int ret, struct addrinfo *addr)
{
	d_data = new Data();
	addPrivateData(&d_data);

	if (ret == -1 || !addr)
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
