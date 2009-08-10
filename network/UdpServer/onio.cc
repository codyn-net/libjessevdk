#include "udpserver.ih"

base::signals::Signal<Glib::IOCondition> &UdpServer::onIO()
{
	return d_data->socket.onIO();
}
