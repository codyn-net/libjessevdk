#include "socket.ih"

Socket::Data::~Data()
{
	close();
}
