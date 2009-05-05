#include "tcpserver.ih"

Socket TcpServer::accept()
{
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);
	
	int fd = ::accept(listenSocket(), reinterpret_cast<struct sockaddr *>(&addr), &len);
	
	return Socket(fd, addr);
}
