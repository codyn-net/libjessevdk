#include "udpserver.hh"
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;
using namespace jessevdk::network;
using namespace jessevdk::base;
using namespace jessevdk::os;

string
UdpServer::Connection()
{
	if (IsMulticast())
	{
		return string("multicast://") + d_data->host + ":" + d_data->port;
	}
	else
	{
		string host;

		if (ListenSocket())
		{
			host = ListenSocket().Address().Host(true);
		}
		else
		{
			host = d_data->host;
		}

		return string("udp://") + host  + ":" + d_data->port;
	}
}

Client
UdpServer::Data::Accept()
{
	/* Cannot accept */
	return Client();
}

UdpServer::DataArgs *
UdpServer::DataArgs::Clone() const
{
	return new DataArgs(*this);
}

UdpServer::DataArgs::DataArgs(int fd, string *buffer, SocketAddress &address)
:
	FileDescriptor::DataArgs(fd, buffer),
	Address(address)
{
}

void
UdpServer::EnableBroadcast()
{
	d_data->broadcast = true;
}

void
UdpServer::Initialize(string const &host, string const &port)
{
	d_data = new Data();

	AddPrivateData(d_data);

	d_data->broadcast = false;

	Set(host, port);
	Server::SetData(d_data);
}

void
UdpServer::InstallIOHandler()
{
	/* NOOP, we use the default */
}

bool
UdpServer::IsMulticast() const
{
	return AddressInfo::IsMulticast(d_data->host);
}

bool
UdpServer::Listen()
{
	return Server::Listen();
}

AddressInfo
UdpServer::ListenAddressInfo()
{
	return AddressInfo::Udp(AddressInfo::IsMulticast(d_data->host) ? "" : d_data->host, d_data->port);
}

bool
UdpServer::ListenOnSocket(network::Socket &socket)
{
	/* UDP servers don't listen */
	if (AddressInfo::IsMulticast(d_data->host))
	{
		SetupMulticast(socket);
	}
	else if (d_data->broadcast)
	{
		SetupBroadcast(socket);
	}

	return true;
}

signals::Signal<int> &
UdpServer::OnClosed()
{
	return d_data->socket.OnClosed();
}

signals::Signal<FileDescriptor::DataArgs> &
UdpServer::OnData()
{
	return d_data->socket.OnData();
}

signals::Signal<Glib::IOCondition> &
UdpServer::OnIO()
{
	return d_data->socket.OnIO();
}

void
UdpServer::Set(string const &host, string const &port)
{
	d_data->host = host;
	d_data->port = port;
}

void
UdpServer::Set(string const &host, size_t port)
{
	stringstream s;
	s << port;

	Set(host, s.str());
}

void UdpServer::Set(string const &port)
{
	Set("", port);
}

void
UdpServer::Set(size_t port)
{
	Set("", port);
}

void
UdpServer::SetupBroadcast(network::Socket &socket)
{
	socket.SetOption(Socket::Options::Broadcast);
}

void
UdpServer::SetupMulticast(network::Socket &socket)
{
	struct ip_mreq mreq;

	mreq.imr_multiaddr.s_addr = inet_addr(d_data->host.c_str());
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);

	setsockopt(socket, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
}

UdpServer::Socket *
UdpServer::Socket::Clone() const
{
	return new Socket(*this);
}

Cloneable<FileDescriptor::DataArgs>
UdpServer::Socket::Data::CreateArgs(int fd, string *buffer)
{
	return UdpServer::DataArgs(fd, buffer, address);
}

Cloneable<Socket>
UdpServer::SocketFromInfo(AddressInfo &info)
{
	d_data->socket = UdpServer::Socket(info);
	return d_data->socket;
}

UdpServer::Socket::Socket(AddressInfo &info)
:
	network::Socket(false)
{
	Data *data = new Data();
	AddPrivateData(data);

	SetData(data);
	SetInfo(info);
}

UdpServer::Socket::Socket(int fd)
:
	network::Socket(fd)
{
}

UdpServer::UdpServer(size_t port)
:
	Client(false)
{
	stringstream s;
	s << port;

	Initialize("", s.str());
}

UdpServer::UdpServer(string const &port)
:
	Client(false)
{
	Initialize("", port);
}

UdpServer::UdpServer(string const &host, size_t port)
:
	Client(false)
{
	stringstream s;
	s << port;

	Initialize(host, s.str());
}

UdpServer::UdpServer(string const &host, string const &port)
:
	Client(false)
{
	Initialize(host, port);
}
