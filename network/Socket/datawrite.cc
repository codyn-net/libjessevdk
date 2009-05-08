#include "socket.ih"

ssize_t Socket::Data::write(char const *buffer, ssize_t len) 
{
	if (writeFunc)
		return (this->*writeFunc)(buffer, len);
	else
		return -1;
}
