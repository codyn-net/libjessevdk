#include "udpserver.ih"

bool UdpServer::listenOnSocket(Socket &socket) 
{
	/* UDP servers don't listen */
	if (d_data->multicast)
	{
		setupMulticast(socket);
	}
	else if (d_data->broadcast)
	{
		setupBroadcast(socket);
	}

	return true;
}
