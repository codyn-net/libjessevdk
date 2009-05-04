#include "tcpconnection.ih"

Connection::Connection(Socket &socket)
:
	FileDescriptor(0)
{
	d_data = new Data(socket);
	addPrivateData(d_data);
	
	construct(socket.socket(), d_data);
	attach();
}
