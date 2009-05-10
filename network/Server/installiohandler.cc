#include "server.ih"

void Server::installIOHandler() 
{
	d_data->listenSocket.onIO().add(*d_data, &Server::Data::onAccept);	
}
