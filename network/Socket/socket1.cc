#include "socket.ih"

Socket::Socket(int socket, struct sockaddr *address, socklen_t size)
:
	FileDescriptor(false)
{
	d_data = new Data();
	addPrivateData(d_data);

	setData(d_data);
		
	if (address)
	{
		d_data->address = SocketAddress(address, size);
	}
	else if (socket != -1)
	{
		struct sockaddr addr;
		socklen_t len = sizeof(addr);
	
		if (getsockname(socket, &addr, &len) == 0)
		{
			struct sockaddr *ptr;
		
			if (addr.sa_family == AF_UNIX)
			{
				struct sockaddr_un ad;
				len = sizeof(ad);
				ptr = reinterpret_cast<struct sockaddr *>(&ad);
			
				if (getsockname(socket, ptr, &len) == 0)
					d_data->address = SocketAddress(ptr, len);
			}
			else
			{
				struct sockaddr_storage ad;
				len = sizeof(sockaddr_storage);
				ptr = reinterpret_cast<struct sockaddr *>(&ad);
			
				if (getsockname(socket, ptr, &len) == 0)
					d_data->address = SocketAddress(ptr, len);
			}
		}
	}
	
	d_data->writeFunc = &Data::writeStream;
	d_data->readFunc = &Data::readStream;
	
	assign(socket);
	attach();
}
