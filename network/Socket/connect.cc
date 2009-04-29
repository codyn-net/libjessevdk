#include "socket.ih"

bool Socket::connect()
{
	if (!*this)
		return false;

	return ::connect(d_data->socket, d_data->info.socketAddress(), d_data->info.socketAddressLength()) == 0;
}
