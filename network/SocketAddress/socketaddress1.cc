#include "socketaddress.ih"

SocketAddress::SocketAddress() 
{
	d_data = new Data();
	addPrivateData(d_data);
	
	d_data->address = 0;	
	d_data->size = 0;
	d_data->cached = Data::Cached::Host | Data::Cached::Port;
}