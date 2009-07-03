#include "socket.ih"

bool Socket::listen(size_t queue)
{
	if (!*this)
		return false;

	return ::listen(fd(), queue) == 0;
}
