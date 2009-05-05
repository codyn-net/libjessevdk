#include "server.ih"
#include <errno.h>
#include <string.h>

bool Server::Data::onAccept(Glib::IOCondition condition)
{
	Socket s = accept();
	
	if (s)
	{
		Connection connection(s);
		
		if (Debug::enabled(Debug::Domain::Network))
		{
			debug_network << "Accepted connection from " << s.address().host() << ":" << s.address().port();
		}
		
		connections.push_back(connection);
		connection.onClosed().add(*this, &Server::Data::onConnectionClosed);

		onNewConnection(connection);
		return true;
	}
	
	return true;
}
