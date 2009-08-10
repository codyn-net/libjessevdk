#include "client.ih"

Client::Client(int fd, struct sockaddr *address, socklen_t size) 
:
	Socket(fd, address, size)
{
}
