#include "udpserver.ih"

UdpServer::Socket::Socket(AddressInfo &info)
:
	network::Socket(false)
{
	Data *data = new Data();
	addPrivateData(data);
	
	setData(data);
	setInfo(info);
}
