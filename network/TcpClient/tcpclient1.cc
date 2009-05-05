#include "tcpclient.ih"

TcpClient::TcpClient(string const &host, string const &port) 
{
	initialize(host, port);
}
