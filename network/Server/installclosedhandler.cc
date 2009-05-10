#include "server.ih"

void Server::installClosedHandler() 
{
	d_data->listenSocket.onClosed().add(*d_data, &Server::Data::onListenClosed);
}
