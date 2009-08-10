#include "udpserver.ih"

bool UdpServer::isMulticast() const
{
	return AddressInfo::isMulticast(d_data->host);
}
