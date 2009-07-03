#include "socketaddress.ih"

SocketAddress::SocketAddress(struct sockaddr const *address, socklen_t size)
{
	d_data = new Data();
	addPrivateData(d_data);

	d_data->address = reinterpret_cast<struct sockaddr *>(malloc(size));
	memcpy(d_data->address, address, size);
	
	d_data->size = size;
	d_data->cached = Data::Cached::None;
}
