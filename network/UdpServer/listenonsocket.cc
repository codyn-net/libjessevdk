#include "udpserver.ih"

bool UdpServer::listenOnSocket(Socket &socket) 
{
	/* UDP servers don't listen */
	
	if (d_data->broadcast)
		socket.setOption(Socket::Options::Broadcast);

	return true;
}
