#include "udpserver.ih"

void UdpServer::initialize(string const &host, string const &port) 
{
	d_data = new Data();
	addPrivateData(d_data);
	
	d_data->host = host;
	d_data->port = port;

	Connection::setData(d_data);
	Server::setData(d_data);
}
