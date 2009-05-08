#include "client.ih"

Client Client::resolve(AddressInfo info)
{
	if (!info)
		return Client();
	
	do
	{
		Client client(info);
		
		if (!client)
		{
			debug_network << "Could not create socket: " << strerror(errno) << endl;
			continue;
		}
		
		if (info.socketType() == AddressInfo::SocketType::Stream && !dynamic_cast<Socket &>(client).connect())
		{
			debug_network << "Could not connect: " << strerror(errno) << endl;
			continue;
		}
		
		if (Debug::enabled(Debug::Domain::Network))
		{
			debug_network << "Connected to " << info.socketAddress().host() << ":" << info.socketAddress().port()  << endl;
		}

		return client;
	} while (info.next());
	
	return Client();
}
