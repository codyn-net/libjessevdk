#include "udpserver.ih"

string UdpServer::connection()
{
	if (isMulticast())
	{
		return string("multicast://") + d_data->host + ":" + d_data->port;
	}
	else
	{
		string host;
		
		if (listenSocket())
		{
			host = listenSocket().address().host(true);
		}
		else
		{
			host = d_data->host;
		}
		
		return string("udp://") + host  + ":" + d_data->port;
	}
}
