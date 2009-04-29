#include "socket.ih"

void Socket::close()
{
	d_data->close();
}
