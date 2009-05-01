#include "tcpserver.ih"

TcpServer::TcpServer(size_t port)
{
	stringstream s;
	s << port;
	
	initialize("", s.str());
}
