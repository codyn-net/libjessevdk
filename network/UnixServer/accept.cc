#include "unixserver.ih"

int UnixServer::accept()
{
	struct sockaddr_un addr;
	socklen_t len = sizeof(addr);
	
	return ::accept(listenSocket(), reinterpret_cast<struct sockaddr *>(&addr), &len);
}
