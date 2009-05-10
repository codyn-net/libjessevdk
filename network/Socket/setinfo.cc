#include "socket.ih"

void Socket::setInfo(AddressInfo &info) 
{
	d_data->info = info;

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
