#include "server.ih"

bool Server::onConnectionClosed(int fd)
{
	for (vector<Connection>::iterator iter = d_data->connections.begin(); iter != d_data->connections.end(); ++iter)
	{
		if (iter->fd() == fd)
		{
			d_data->connections.erase(iter);
			break;
		}
	}
	
	return false;
}
