#include "tcpserver.ih"

Client TcpServer::Data::accept()
{
	struct sockaddr_storage addr;
	socklen_t len = sizeof(addr);
	
	struct sockaddr *ad = reinterpret_cast<struct sockaddr *>(&addr);
	
	int fd = ::accept(*listenSocket, ad, &len);
	
	return Client(fd, ad, len);
}
