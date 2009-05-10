#include "socket.ih"

ssize_t Socket::Data::readDgram(char *buffer, ssize_t len) 
{
	struct sockaddr_in addr;
	struct sockaddr *add = reinterpret_cast<struct sockaddr *>(&addr);
	ssize_t ret;

	socklen_t addrlen = sizeof(addr);
	
	ret = ::recvfrom(fd, buffer, len, 0, add, &addrlen);
	
	if (ret >= 0)
	{
		address = SocketAddress(add, addrlen);

		/*if (Debug::enabled(Debug::Domain::Network))
		{
			debug_network << "Received datagram style (" << ret << "): " << address.host() << ":" << address.port() << endl;
		}*/
	}
	
	return ret;
}
