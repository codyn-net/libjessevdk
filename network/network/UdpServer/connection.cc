#include "udpserver.ih"

string UdpServer::connection()
{
	string host = listenSocket().address().host(true);
	
	if (d_data->multicast)
	{
		return string("multicast://") + host + ":" + d_data->port;
	}
	else
	{
		return string("udp://") + host  + ":" + d_data->port;
	}
}
