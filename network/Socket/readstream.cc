#include "socket.ih"

ssize_t Socket::Data::readStream(char *buffer, ssize_t len) 
{
	cout << "Reading stream style" << endl;
	return ::recv(fd, buffer, len, 0);
}
