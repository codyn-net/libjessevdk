#include "tcpconnection.ih"

bool TcpConnection::Data::onSocketClosed()
{
	close();
	return false;
}
