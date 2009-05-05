#include "tcpserver.ih"

TcpServer::TcpServer(string const &port)
{
	initialize("0.0.0.0", port);
}
