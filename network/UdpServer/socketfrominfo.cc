#include "udpserver.ih"

Cloneable<Socket> UdpServer::socketFromInfo(AddressInfo &info) 
{
	d_data->socket = UdpServer::Socket(info);
	return d_data->socket;
}
