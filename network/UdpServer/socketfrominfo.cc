#include "udpserver.ih"

Socket &UdpServer::socketFromInfo(AddressInfo &info) 
{
	setInfo(info);
	return *this;
}
