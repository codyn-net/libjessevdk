#include "socket.ih"
#include <iostream>

Socket::Socket(AddressInfo info)
:
	FileDescriptor(false)
{
	d_data = new Data();
	addPrivateData(d_data);
	
	d_data->info = info;
	d_data->writeFunc = 0;
	d_data->readFunc = 0;

	setData(d_data);

	if (info)
	{
		d_data->address = info.socketAddress();

		assign(::socket(info.family(), info.socketType(), info.protocol()));
		attach();
		
		if (info.socketType() == SOCK_DGRAM)
		{
			d_data->writeFunc = &Data::writeDgram;
			d_data->readFunc = &Data::readDgram;
		}
		else
		{
			d_data->writeFunc = &Data::writeStream;
			d_data->readFunc = &Data::readStream;
		}
	}	
}
