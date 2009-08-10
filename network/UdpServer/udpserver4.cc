#include "udpserver.ih"

UdpServer::UdpServer(string const &host, string const &port)
:
	Client(false)
{
	initialize(host, port);
}
