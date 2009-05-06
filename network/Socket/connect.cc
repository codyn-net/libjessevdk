#include "socket.ih"

bool Socket::connect()
{
	if (!*this)
		return false;

	return ::connect(fd(), d_data->info.socketAddress(), d_data->info.socketAddress().length()) == 0;
}
