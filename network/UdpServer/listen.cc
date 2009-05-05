#include "udpserver.ih"

bool UdpServer::listen() 
{
	bool ret = Server::listen();
	
	if (ret && listenSocket())
		setSocket(listenSocket());
	
	return ret;
}
