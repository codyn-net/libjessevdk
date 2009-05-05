#include "udpserver.ih"

int UdpServer::Data::recv(string &data) 
{
	char buffer[1024];
	ssize_t len;
	
	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(addr);
	
	len = ::recvfrom(this->fd, buffer, 1024 - 1, 0, reinterpret_cast<struct sockaddr *>(&addr), &addrlen);
	
	if (len >= 0)
	{
		address = addr;
		buffer[len] = '\0';
	}
	
	data = buffer;
	return len;
}
