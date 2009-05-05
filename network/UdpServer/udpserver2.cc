#include "udpserver.ih"

UdpServer::UdpServer(string const &port)
:
	Connection(false) 
{
	initialize("0.0.0.0", port);
}
