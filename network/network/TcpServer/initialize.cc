#include "tcpserver.ih"

void TcpServer::initialize(string const &host, string const &port)
{
	d_data = new Data();
	addPrivateData(d_data);
	
	set(host, port);
	setData(d_data);
}
