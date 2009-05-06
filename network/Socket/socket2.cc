#include "socket.ih"
#include <iostream>

Socket::Socket(AddressInfo info)
:
	FileDescriptor(false)
{
	d_data = new Data();
	addPrivateData(d_data);
	
	d_data->info = info;

	setData(d_data);

	if (info)
	{
		assign(::socket(info.family(), info.socketType(), info.protocol()));
		attach();
	}	
}
