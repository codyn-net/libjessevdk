#include "udpserver.ih"

UdpServer::UdpServer(size_t port)
:
	Client(false)
{
	stringstream s;
	s << port;
	
	initialize("", s.str());
}
