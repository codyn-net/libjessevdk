#include "client.ih"

bool Client::connect() 
{
	AddressInfo info = connectAddressInfo();
	
	if (!info)
		return;
	
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
		
		setSocket(socket);
		break;
	} while (info.next());
}
