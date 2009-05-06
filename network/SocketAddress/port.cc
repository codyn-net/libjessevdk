#include "socketaddress.ih"

string const &SocketAddress::port() const
{
	if (d_data->cached & Data::Cached::Port)
		return d_data->port;

	char port[255];
	port[0] = '\0';

	int ret = getnameinfo(d_data->address,
	                      d_data->size,
	                      0, 0,
	                      port, sizeof(port),
	                      0);

	if (d_data->address->sa_family == AF_UNIX && d_data->size == 2)
		d_data->port = "";
	else
		d_data->port = ret == 0 ? port : "";

	d_data->cached |= Data::Cached::Port;

	return d_data->port;
}
