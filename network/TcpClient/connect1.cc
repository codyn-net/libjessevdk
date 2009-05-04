#include "tcpclient.ih"
#include <errno.h>
#include <string.h>

Connection TcpClient::connect(string const &host, string const &port)
{
	AddressInfo info(host, port);
	
	if (!info)
		return Connection();
	
	do
	{
		Socket socket(info);
		
		if (!socket)
		{
			cerr << "Could not create socket: " << strerror(errno) << endl;
			continue;
		}
		
		if (!socket.connect())
		{
			cerr << "Could not connect: " << strerror(errno) << endl;
			continue;
		}
		
		return Connection(socket, *reinterpret_cast<struct sockaddr_in *>(info.socketAddress()));
	} while (info.next());
	
	return Connection();
}
