#include "server.ih"

void Server::Data::onConnectionClosed(int fd)
{
	for (vector<Client>::iterator iter = connections.begin(); iter != connections.end(); ++iter)
	{
		if (iter->fd() == fd)
		{
			connections.erase(iter);
			break;
		}
	}
}
