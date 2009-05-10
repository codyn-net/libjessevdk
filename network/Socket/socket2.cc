#include "socket.ih"
#include <iostream>

Socket::Socket(AddressInfo info)
:
	FileDescriptor(false)
{
	d_data = new Data();
	addPrivateData(d_data);

	d_data->writeFunc = 0;
	d_data->readFunc = 0;
		
	setData(d_data);
	setInfo(info);
}
