#include "socket.ih"

Socket::Socket(int socket, struct sockaddr *address, socklen_t size)
:
	FileDescriptor(false)
{
	d_data = new Data();
	addPrivateData(d_data);
	
	d_data->address = SocketAddress(address, size);
	
	setData(d_data);
	
	d_data->writeFunc = &Data::writeStream;
	d_data->readFunc = &Data::readStream;
	
	assign(socket);
	attach();
}
