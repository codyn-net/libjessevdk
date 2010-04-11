#include "socketaddress.hh"

#include <string.h>
#include <errno.h>

using namespace std;
using namespace jessevdk::network;

SocketAddress::Data::~Data()
{
	if (address)
	{
		free(address);
	}
}

string const &
SocketAddress::Host(bool numeric) const
{
	if (d_data->cached & Data::Cached::Host)
	{
		return d_data->host;
	}

	char host[255];
	host[0] = '\0';

	int ret = getnameinfo(d_data->address,
	                      d_data->size,
	                      host, sizeof(host),
	                      0, 0,
	                      numeric ? NI_NUMERICHOST : 0);

	d_data->host = ret == 0 ? host : "";
	d_data->cached |= Data::Cached::Host;

	return d_data->host;
}

string const &
SocketAddress::Port(bool numeric) const
{
	if (d_data->cached & Data::Cached::Port)
	{
		return d_data->port;
	}

	char port[255];
	port[0] = '\0';

	int ret = getnameinfo(d_data->address,
	                      d_data->size,
	                      0, 0,
	                      port, sizeof(port),
	                      numeric ? NI_NUMERICSERV : 0);

	if (d_data->address->sa_family == AF_UNIX && d_data->size == 2)
	{
		d_data->port = "";
	}
	else
	{
		d_data->port = ret == 0 ? port : "";
	}

	d_data->cached |= Data::Cached::Port;

	return d_data->port;
}

SocketAddress::SocketAddress()
{
	d_data = new Data();
	AddPrivateData(d_data);

	d_data->address = 0;
	d_data->size = 0;
	d_data->cached = Data::Cached::Host | Data::Cached::Port;
}

SocketAddress::SocketAddress(struct sockaddr const *address, socklen_t size)
{
	d_data = new Data();
	AddPrivateData(d_data);

	d_data->address = reinterpret_cast<struct sockaddr *>(malloc(size));
	memcpy(d_data->address, address, size);

	d_data->size = size;
	d_data->cached = Data::Cached::None;
}
