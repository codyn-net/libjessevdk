#include "udpserver.ih"

UdpServer::UdpServer(string const &port)
:
	Client(false) 
{
	initialize("0.0.0.0", port);
}
