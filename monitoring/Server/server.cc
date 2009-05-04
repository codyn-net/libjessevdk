#include "server.ih"

Server::Server(string const &host, string const &port)
{
	d_data = new Data(host, port);
	addPrivateData(&d_data);
	
	d_data->server.listen();
}
