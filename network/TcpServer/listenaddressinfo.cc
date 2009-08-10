#include "tcpserver.ih"

AddressInfo TcpServer::listenAddressInfo() 
{
	return AddressInfo::Tcp(d_data->host, d_data->port);
}
