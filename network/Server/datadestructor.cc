#include "server.ih"

Server::Data::~Data()
{
	close();
}
