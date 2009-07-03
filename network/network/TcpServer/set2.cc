#include "tcpserver.ih"

void TcpServer::set(string const &host, size_t port) 
{
	stringstream s;
	s << port;
	
	set(host, s.str());
}
