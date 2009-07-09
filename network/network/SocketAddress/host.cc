#include "socketaddress.ih"

string const &SocketAddress::host(bool numeric) const
{
	if (d_data->cached & Data::Cached::Host)
		return d_data->host;
		
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