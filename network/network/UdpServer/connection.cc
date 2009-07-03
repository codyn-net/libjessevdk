#include "udpserver.ih"

string UdpServer::connection()
{
	return string("udp://") + listenSocket().address().host(true) + ":" + d_data->port;
}
