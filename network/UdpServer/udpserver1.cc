#include "udpserver.ih"

UdpServer::UdpServer(size_t port) 
{
	stringstream s;
	s << port;
	
	initialize("localhost", s.str());
}
