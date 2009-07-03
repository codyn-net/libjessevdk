#include "socket.ih"

bool Socket::connect()
{
	if (!*this)
		return false;

	if (Debug::enabled(Debug::Domain::Network))
	{
		debug_network << "Connecting: " << d_data->info.socketAddress().host(true) << ":" << d_data->info.socketAddress().port(true) << endl;
	}
	
	return ::connect(fd(), d_data->info.socketAddress(), d_data->info.socketAddress().length()) == 0;
}
