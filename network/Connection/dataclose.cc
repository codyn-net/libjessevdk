#include "tcpconnection.ih"

void Connection::Data::close()
{
	socket.close();
}
