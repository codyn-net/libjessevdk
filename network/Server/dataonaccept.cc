#include "server.ih"
#include <errno.h>
#include <string.h>

bool Server::Data::onAccept(Glib::IOCondition condition)
{
	Client client = accept();
	
	if (client)
	{
		/*if (Debug::enabled(Debug::Domain::Network))
		{
			debug_network << "Accepted connection from " << client.address().host() << ":" << client.address().port() << endl;
		}*/
		
		connections.push_back(client);
		client.onClosed().add(*this, &Server::Data::onConnectionClosed);

		onNewConnection(client);
	}

	return true;
}
