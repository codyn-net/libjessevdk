#include "udpserver.ih"

void UdpServer::setupMulticast(network::Socket &socket) 
{
	struct ip_mreq mreq;
	
	mreq.imr_multiaddr.s_addr = inet_addr(d_data->host.c_str());
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);
	
	setsockopt(socket, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
}
