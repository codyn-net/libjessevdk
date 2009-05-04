#include "socket.ih"

Socket::Socket(int socket)
{
	d_data = new Data();
	addPrivateData(&d_data);
	
	d_data->socket = socket;
}
