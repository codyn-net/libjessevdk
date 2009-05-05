#include "socketaddress.ih"

string const &SocketAddress::host() const
{
	if (d_data->cached & Data::Cached::Host)
		return d_data->host;
		
	char host[255];

	int ret = getnameinfo(reinterpret_cast<struct sockaddr *>(&d_data->address),
	                      sizeof(d_data->address),
	                      host, sizeof(host),
	                      0, 0,
	                      0);

	d_data->host = ret == 0 ? host : "";
	d_data->cached |= Data::Cached::Host;

	return d_data->host;
}
