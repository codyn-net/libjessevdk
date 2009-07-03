#include "udpserver.ih"

UdpServer::UdpServer(string const &port)
:
	Client(false) 
{
	initialize("", port);
}
