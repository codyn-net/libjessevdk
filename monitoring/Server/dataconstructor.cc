#include "server.ih"

Server::Data::Data(string const &host, string const &port) 
:
	server(host, port)
{
}
