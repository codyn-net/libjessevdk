#include "socket.ih"

Socket::Socket(int socket)
:
	FileDescriptor(false)
{
	d_data = new Data();
	addPrivateData(d_data);
	
	setData(d_data);
	
	assign(socket);
	attach();
}
