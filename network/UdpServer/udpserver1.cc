#include "udpserver.ih"

UdpServer::UdpServer(size_t port)
:
	Connection(false)
{
	stringstream s;
	s << port;
	
	initialize("0.0.0.0", s.str());
}
