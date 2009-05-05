#include "connection.ih"

Connection::Connection(Socket &socket)
:
	FileDescriptor(static_cast<Data *>(0))
{
	d_data = new Data();
	addPrivateData(d_data);
	
	setData(d_data);
	assign(-1);

	setSocket(socket);
}
