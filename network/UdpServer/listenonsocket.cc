#include "udpserver.ih"

bool UdpServer::listenOnSocket(Socket &socket) 
{
	/* UDP servers don't listen */
	return true;
}
