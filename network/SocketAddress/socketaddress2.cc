#include "socketaddress.ih"

SocketAddress::SocketAddress(struct sockaddr_in const &address) 
{
	d_data = new Data();
	addPrivateData(d_data);

	d_data->address = address;
	d_data->cached = Data::Cached::None;
}
