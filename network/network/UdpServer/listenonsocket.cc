#include "udpserver.ih"

bool UdpServer::listenOnSocket(network::Socket &socket) 
{
	/* UDP servers don't listen */
	if (AddressInfo::isMulticast(d_data->host))
	{
		setupMulticast(socket);
	}
	else if (d_data->broadcast)
	{
		setupBroadcast(socket);
	}

	return true;
}
