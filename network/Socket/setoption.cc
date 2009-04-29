#include "socket.ih"

bool Socket::setOption(Options::Values option)
{
	if (!*this)
		return false;

	int one = 1;
	return setsockopt(d_data->socket, SOL_SOCKET, option, &one, sizeof(one)) == 0;
}
