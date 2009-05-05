#include "client.ih"

bool Client::connect() 
{
	AddressInfo info = connectAddressInfo();
	
	if (!info)
		return false;
	
	do
	{
		Socket socket(info);
		
		if (!socket)
		{
			debug_network << "Could not create socket: " << strerror(errno) << endl;
			continue;
		}
		
		if (!socket.connect())
		{
			debug_network << "Could not connect: " << strerror(errno) << endl;
			continue;
		}
		
		setSocket(socket);
		
		if (Debug::enabled(Debug::Domain::Network))
		{
			debug_network << "Connected to " << info.socketAddress().host() << ":" << info.socketAddress().port()  << endl;
		}

		return true;
	} while (info.next());
	
	return false;
}
