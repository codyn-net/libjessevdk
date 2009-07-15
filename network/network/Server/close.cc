#include "server.ih"

void Server::close() 
{
	d_data->listenSocket->close();
}
