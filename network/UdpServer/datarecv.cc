#include "udpserver.ih"

int UdpServer::Data::recv(string &data) 
{
	char buffer[1024];
	ssize_t len;
	
	struct sockaddr_in addr;
	struct sockaddr *add = reinterpret_cast<struct sockaddr *>(&addr);

	socklen_t addrlen = sizeof(addr);
	
	len = ::recvfrom(fd, buffer, 1024 - 1, 0, add, &addrlen);
	
	if (len >= 0)
	{
		address = SocketAddress(add, addrlen);
		buffer[len] = '\0';
	}
	
	data = buffer;
	return len;
}
