#include "udpserver.ih"

UdpServer::UdpServer(string const &host, size_t port) 
{
	stringstream s;
	s << port;
	
	initialize(string, s.str());
}
