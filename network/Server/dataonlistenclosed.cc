#include "server.ih"

void Server::Data::onListenClosed(int fd) 
{
	debug_network << "Server stopped listening" << endl;
}
