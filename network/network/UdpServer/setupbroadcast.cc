#include "udpserver.ih"

void UdpServer::setupBroadcast(Socket &socket) 
{
	socket.setOption(Socket::Options::Broadcast);
}
