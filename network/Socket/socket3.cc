#include "socket.ih"

Socket::Socket(int socket, struct sockaddr *address, socklen_t size)
{
	d_data = new Data();
	addPrivateData(d_data);
	
	d_data->socket = socket;
	d_data->address = SocketAddress(address, size);
}
