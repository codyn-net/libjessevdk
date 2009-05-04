#include "tcpconnection.ih"

TcpConnection::Data::Data(Socket &socket, struct sockaddr_in const &address)
:
	socket(socket),
	address(address)
{
	if (socket)
	{
		socket.onClosed().add(*this, &TcpConnection::Data::onSocketClosed);
	}
}
