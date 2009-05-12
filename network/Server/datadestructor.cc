#include "server.ih"

Server::Data::~Data() 
{
	for (vector<Client>::iterator iter = connections.begin(); iter != connections.end(); ++iter)
	{
		iter->onClosed().remove(*this, &Server::Data::onConnectionClosed);
	}	
}
