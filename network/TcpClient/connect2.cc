#include "tcpclient.ih"

Connection TcpClient::connect(string const &host, size_t port)
{
	stringstream s;
	
	s << port;
	return connect(host, s.str());
}
