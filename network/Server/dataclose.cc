#include "server.ih"

void Server::Data::close()
{
	if (listenSource)
		listenSource->destroy();
}
