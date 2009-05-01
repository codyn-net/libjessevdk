#include "tcpserver.ih"

void TcpServer::Data::close()
{
	if (listenSource)
		listenSource->destroy();
}
