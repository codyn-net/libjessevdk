#include "udpserver.ih"

UdpServer::UdpServer(string const &host, string const &port)
:
	Connection(false)
{
	initialize(host, port);
}
