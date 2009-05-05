#include "tcpserver.ih"

TcpServer::TcpServer(size_t port)
{
	stringstream s;
	s << port;
	
	initialize("0.0.0.0", s.str());
}
