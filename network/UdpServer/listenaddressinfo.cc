#include "udpserver.ih"

AddressInfo UdpServer::listenAddressInfo() 
{
	return AddressInfo::Udp(d_data->host, d_data->port);
}
