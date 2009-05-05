#include "socket.ih"

bool Socket::bind()
{
	if (!*this)
		return false;

	return ::bind(d_data->socket, d_data->info.socketAddress(), d_data->info.socketAddress().length()) == 0;
}
