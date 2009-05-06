#include "socket.ih"

void Socket::setData(Data *data) 
{
	d_data = data;
	FileDescriptor::setData(data);
}
