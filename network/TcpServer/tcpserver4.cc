#include "tcpserver.ih"

TcpServer::TcpServer(string const &port)
{
	initialize("localhost", port);
}
