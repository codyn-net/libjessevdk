#include "udpserver.ih"

void UdpServer::setupBroadcast(network::Socket &socket) 
{
	socket.setOption(Socket::Options::Broadcast);
}
