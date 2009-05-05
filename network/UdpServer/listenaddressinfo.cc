#include "udpserver.ih"

AddressInfo UdpServer::listenAddressInfo() 
{
	struct addrinfo hint;

	memset(&hint, 0, sizeof(hint));
	
	hint.ai_flags = 0;
	hint.ai_family = AF_UNSPEC;
	hint.ai_socktype = SOCK_DGRAM;
	hint.ai_protocol = IPPROTO_UDP;

	return AddressInfo(d_data->host, d_data->port, hint);
}
