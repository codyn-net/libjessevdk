#include "server.ih"
#include <errno.h>
#include <string.h>

bool Server::onAccept(Glib::IOCondition condition)
{
	Socket s = accept();
	
	if (s)
	{
		Connection connection(s);
		
		if (Debug::enabled(Debug::Domain::Network))
		{
			debug_network << "Accepted connection from " << s.address().host() << ":" << s.address().port();
		}
		
		d_data->connections.push_back(connection);
		connection.onClosed().add(*this, &Server::onConnectionClosed);

		d_data->onNewConnection(connection);
		return true;
	}
	
	return true;
}
