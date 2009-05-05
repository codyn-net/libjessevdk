#include "server.ih"
#include <errno.h>
#include <string.h>

bool Server::onAccept(Glib::IOCondition condition)
{
	Socket s = accept();
	
	if (s)
	{
		Connection connection(s);
		
		d_data->connections.push_back(connection);
		connection.onClosed().add(*this, &Server::onConnectionClosed);

		d_data->onNewConnection(connection);
		return true;
	}
	
	return true;
}
