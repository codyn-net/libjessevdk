#include "socket.ih"

ssize_t Socket::Data::readStream(char *buffer, ssize_t len) 
{
	ssize_t ret = ::recv(fd, buffer, len, 0);

	/*if (ret > 0 && Debug::enabled(Debug::Domain::Network))
	{
		debug_network << "Received stream style: " << address.host() << ":" << address.port() << endl;
	}*/

	return ret;
}
