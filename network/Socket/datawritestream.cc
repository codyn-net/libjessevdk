#include "socket.ih"

ssize_t Socket::Data::writeStream(char const *buffer, ssize_t len) 
{
	//debug_network << "Writing stream style" << endl;
	return ::send(fd, buffer, len, MSG_NOSIGNAL);
}
