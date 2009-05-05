#include "tcpserver.ih"

bool TcpServer::listenOnSocket(Socket &socket) 
{
	return socket.listen(20);
}
