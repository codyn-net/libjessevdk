#include "udpserver.ih"

base::signals::Signal<os::FileDescriptor::DataArgs> &UdpServer::onData()
{
	return d_data->socket.onData();
}
