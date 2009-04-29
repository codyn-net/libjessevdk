#include "socket.ih"

bool Socket::listen(size_t queue)
{
	if (!*this)
		return false;

	return ::listen(d_data->socket, queue) == 0;
}
