#include "tcpconnection.ih"

TcpConnection::TcpConnection(Socket &socket, struct sockaddr_in const &address)
{
	d_data = new Data(socket, address);
	addPrivateData(&d_data);
}
