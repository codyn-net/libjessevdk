#include "unixserver.ih"

Socket UnixServer::Data::accept()
{
	struct sockaddr_un addr;
	socklen_t len = sizeof(addr);
	struct sockaddr *ad = reinterpret_cast<struct sockaddr *>(&addr);
	
	int fd = ::accept(listenSocket, ad, &len);
	
	return Socket(fd, ad, len);
}
