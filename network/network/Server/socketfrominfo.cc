#include "server.ih"

Socket &Server::socketFromInfo(AddressInfo &info) 
{
	d_data->listenSocket = Socket(info);
	return d_data->listenSocket;
}
