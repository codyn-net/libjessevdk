#include "socket.ih"

ssize_t Socket::Data::read(char *buffer, ssize_t len) 
{
	if (readFunc)
		return (this->*readFunc)(buffer, len);
	else
		return -1;
}
