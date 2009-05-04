#include "socket.ih"
#include <iostream>

Socket::Socket(AddressInfo info)
{
	d_data = new Data();
	addPrivateData(d_data);
	
	d_data->info = info;

	if (info)
		d_data->socket = ::socket(info.family(), info.socketType(), info.protocol());
	else
		d_data->socket = -1;
}
