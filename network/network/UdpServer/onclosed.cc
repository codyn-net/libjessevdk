#include "udpserver.ih"

base::signals::Signal<int> &UdpServer::onClosed()
{
	return d_data->socket.onClosed();
}
