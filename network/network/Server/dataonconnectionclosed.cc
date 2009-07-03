#include "server.ih"

void Server::Data::onConnectionClosed(int fd)
{
	for (vector<Client>::iterator iter = connections.begin(); iter != connections.end(); ++iter)
	{
		if (iter->fd() == fd)
		{
			if (Debug::enabled(Debug::Domain::Network))
			{
				debug_network << "Disconnected " << iter->address().host() << ":" << iter->address().port() << endl;
			}

			connections.erase(iter);
			break;
		}
	}
}
