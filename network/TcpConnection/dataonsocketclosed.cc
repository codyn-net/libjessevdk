#include "tcpconnection.ih"

bool TcpConnection::Data::onSocketClosed()
{
	onClosed();
	return false;
}
