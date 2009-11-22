#include "server.hh"
#include <sstream>
#include <errno.h>
#include <string.h>

#include <jessevdk/base/debug.hh>

using namespace jessevdk::network;
using namespace std;
using namespace jessevdk::base;

void
Server::Close()
{
	d_data->listenSocket->Close();
}

Server::Data::~Data()
{
	for (vector<Client>::iterator iter = connections.begin(); iter != connections.end(); ++iter)
	{
		iter->OnClosed().Remove(*this, &Server::Data::OnConnectionClosed);
	}
}

bool
Server::Data::OnAccept(Glib::IOCondition condition)
{
	Client client = Accept();

	if (client)
	{
		if (Debug::Enabled(Debug::Domain::Network))
		{
			debug_network << "Accepted connection from " << client.Address().Host() << ":" << client.Address().Port() << endl;
		}

		connections.push_back(client);
		client.OnClosed().Add(*this, &Server::Data::OnConnectionClosed);

		onNewConnection(client);
	}

	return true;
}

void
Server::Data::OnConnectionClosed(int fd)
{
	for (vector<Client>::iterator iter = connections.begin(); iter != connections.end(); ++iter)
	{
		if (iter->Fd() == fd)
		{
			if (Debug::Enabled(Debug::Domain::Network))
			{
				debug_network << "Disconnected " << iter->Address().Host() << ":" << iter->Address().Port() << endl;
			}

			connections.erase(iter);
			break;
		}
	}
}

void
Server::Data::OnListenClosed(int fd)
{
	debug_network << "Server stopped listening" << endl;
}

void
Server::InstallClosedHandler()
{
	d_data->listenSocket->OnClosed().Add(*d_data, &Server::Data::OnListenClosed);
}

void
Server::InstallIOHandler()
{
	d_data->listenSocket->OnIO().Add(*d_data, &Server::Data::OnAccept);
}

bool
Server::Listen()
{
	AddressInfo info(ListenAddressInfo());

	do
	{
		Cloneable<Socket> socket = SocketFromInfo(info);

		if (!*socket)
		{
			debug_network << "Could not create socket: " << strerror(errno) << endl;
			continue;
		}

		if (!socket->SetOption(Socket::Options::Reuse))
		{
			debug_network << "Could not reuse socket: " << strerror(errno) << endl;
			continue;
		}

		if (!socket->Bind())
		{
			debug_network << "Could not bind socket: " << strerror(errno) << endl;
			continue;
		}

		if (!ListenOnSocket(socket))
		{
			debug_network << "Could not listen on socket: "  << strerror(errno) << endl;
			continue;
		}

		if (Debug::Enabled(Debug::Domain::Network))
		{
			debug_network << "Listening on " << info.SocketAddress().Host(true) << ":" << info.SocketAddress().Port(true) << endl;
		}

		d_data->listenSocket = socket;

		InstallIOHandler();
		InstallClosedHandler();

		return true;
	} while (info.Next());

	return false;
}

Server::Server()
:
	d_data(0)
{
}

void
Server::SetData(Data *data)
{
	d_data = data;
}

Cloneable<Socket>
Server::SocketFromInfo(AddressInfo &info)
{
	return Socket(info);
}
