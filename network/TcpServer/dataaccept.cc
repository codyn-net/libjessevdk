#include "tcpserver.ih"

Socket TcpServer::Data::accept()
{
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);
	
	struct sockaddr *ad = reinterpret_cast<struct sockaddr *>(&addr);
	
	int fd = ::accept(listenSocket, ad, &len);
	
	return Socket(fd, ad, len);
}
