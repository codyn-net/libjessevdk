#include "socket.ih"

Socket::Socket(bool createData)
:
	FileDescriptor(createData)
{
	d_data = 0;

	if (!createData)
		return;
	
	d_data = new Data();
	addPrivateData(d_data);
}
