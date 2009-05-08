#include "socket.ih"

ssize_t Socket::Data::writeDgram(char const *buffer, ssize_t len) 
{
	if (Debug::enabled(Debug::Domain::Network))
	{
		debug_network << "Writing datagram style: " << address.host() << ":" << address.port() << endl;
	}

	return ::sendto(fd, buffer, len, 0, address, address.length());
}
