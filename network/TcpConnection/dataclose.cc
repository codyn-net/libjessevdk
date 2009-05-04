#include "tcpconnection.ih"

void TcpConnection::Data::close()
{
	socket.close();
}
