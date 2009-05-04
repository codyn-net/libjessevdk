#include "connection.ih"

Connection::Data::Data(Socket &socket)
:
	socket(socket)
{
	if (socket)
	{
		socket.onClosed().add(*this, &Connection::Data::onSocketClosed);
	}
}
