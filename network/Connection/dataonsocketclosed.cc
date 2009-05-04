#include "connection.ih"

bool Connection::Data::onSocketClosed()
{
	close();
	return false;
}
