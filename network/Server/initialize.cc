#include "server.ih"

void Server::initialize()
{
	d_data = new Data();
	addPrivateData(d_data);
}
