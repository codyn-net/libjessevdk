#include "udpserver.ih"

void UdpServer::set(string const &host, size_t port) 
{
	stringstream s;
	s << port;
	
	set(host, s.str());
}
