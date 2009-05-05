#include "udpserver.ih"

UdpServer::UdpServer(string const &host, size_t port)
:
	Connection(false)
{
	stringstream s;
	s << port;
	
	initialize(host, s.str());
}
