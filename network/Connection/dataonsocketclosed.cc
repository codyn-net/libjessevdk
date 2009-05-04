#include "tcpconnection.ih"

bool Connection::Data::onSocketClosed()
{
	close();
	return false;
}
