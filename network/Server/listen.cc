#include "server.ih"
#include <iostream>
#include <errno.h>
#include <string.h>

bool Server::listen()
{
	AddressInfo info(listenAddressInfo());

	do
	{
		Socket socket(info);
		
		if (!socket)
		{
			debug_network << "Could not create socket: " << strerror(errno) << endl;
			continue;
		}
		
		if (!socket.setOption(Socket::Options::Reuse))
		{
			debug_network << "Could not reuse socket: " << strerror(errno) << endl;
			continue;
		}
		
		if (!socket.bind())
		{
			debug_network << "Could not bind socket: " << strerror(errno) << endl;
			continue;
		}
		
		if (!listenOnSocket(socket))
		{
			debug_network << "Could not listen on socket: "  << strerror(errno) << endl;
			continue;
		}
		
		if (Debug::enabled(Debug::Domain::Network))
		{
			debug_network << "Listening on " << info.socketAddress().host() << ":" << info.socketAddress().port() << endl;
		}
		
		d_data->listenSocket = socket;
		
		/* Add to the main loop to be polled */
		d_data->listenSource = Glib::IOSource::create(socket, Glib::IO_IN);

		d_data->listenSource->connect(sigc::mem_fun(*this, &Server::onAccept));
		d_data->listenSource->attach();

		return true;
	} while (info.next());
	
	return false;
}
