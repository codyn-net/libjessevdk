#include "connection.ih"

Connection::Connection(Socket &socket)
:
	FileDescriptor(0)
{
	d_data = new Data();
	addPrivateData(d_data);
	
	construct(-1, d_data);
	setSocket(socket);
}
