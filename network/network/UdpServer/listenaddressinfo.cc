#include "udpserver.ih"

AddressInfo UdpServer::listenAddressInfo() 
{
	return AddressInfo::Udp(AddressInfo::isMulticast(d_data->host) ? "" : d_data->host, d_data->port);	
}
