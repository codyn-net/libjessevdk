#include "socket.ih"

bool Socket::setOption(Options::Values option)
{
	if (!*this)
		return false;

	int one = 1;
	return setsockopt(fd(), SOL_SOCKET, option, &one, sizeof(one)) == 0;
}
