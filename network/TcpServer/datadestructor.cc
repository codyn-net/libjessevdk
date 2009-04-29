#include "tcpserver.ih"

TcpServer::Data::~Data()
{
	close();
}
