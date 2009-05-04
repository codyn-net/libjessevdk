#include "connection.ih"

void Connection::Data::close()
{
	socket.close();
}
