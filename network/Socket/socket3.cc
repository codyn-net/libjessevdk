#include "socket.ih"

Socket::Socket(int socket, struct sockaddr_in &address) 
{
	d_data = new Data();
	addPrivateData(d_data);
	
	d_data->socket = socket;
	d_data->address = address;
}
