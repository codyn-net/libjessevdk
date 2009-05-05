#include "tcpclient.ih"

TcpClient::TcpClient(string const &host, size_t port) 
{
	stringstream s;
	s << port;
	
	initialize(host, s.str());
}
