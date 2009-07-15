#include "udpserver.ih"

void UdpServer::initialize(string const &host, string const &port) 
{
	d_data = new Data();
	
	addPrivateData(d_data);
	
	d_data->broadcast = false;

	set(host, port);
	Server::setData(d_data);
}
