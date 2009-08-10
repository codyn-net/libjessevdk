#include "tcpserver.ih"

string TcpServer::connection()
{
	return string("tcp://") + listenSocket().address().host(true) + ":" + d_data->port;
}
