#include "tcpserver.ih"

AddressInfo TcpServer::listenAddressInfo() 
{
	return AddressInfo(d_data->host, d_data->port);
}
