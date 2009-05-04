#include "tcpconnection.ih"

TcpConnection::TcpConnection(Socket &socket, struct sockaddr_in const &address)
:
	FileDescriptor(0)
{
	d_data = new Data(socket, address);
	addPrivateData(d_data);
	
	construct(socket.socket(), d_data);
	attach();
}
