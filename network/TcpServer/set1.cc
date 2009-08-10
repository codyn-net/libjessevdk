#include "tcpserver.ih"

void TcpServer::set(string const &host, string const &port) 
{
	d_data->host = host;
	d_data->port = port;
}
