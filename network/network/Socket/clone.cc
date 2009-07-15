#include "socket.ih"

Socket *Socket::clone() const
{
	return new Socket(*this);
}
