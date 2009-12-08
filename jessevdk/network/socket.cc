#include "socket.hh"

#include <sys/un.h>
#include <jessevdk/base/debug.hh>

using namespace jessevdk::network;
using namespace jessevdk::base;
using namespace std;

#ifdef HAVE_CONFIG_H
#include <jessevdk/config.hh>
#endif

#ifndef PLATFORM_OSX
#define SEND_FLAGS MSG_NOSIGNAL
#else
#define SEND_FLAGS 0
#endif

bool
Socket::Bind()
{
	if (!*this)
	{
		return false;
	}

	return ::bind(Fd(), d_data->info.SocketAddress(), d_data->info.SocketAddress().Length()) == 0;
}

Socket *
Socket::Clone() const
{
	return new Socket(*this);
}

bool
Socket::Connect()
{
	if (!*this)
	{
		return false;
	}

	if (Debug::Enabled(Debug::Domain::Network))
	{
		debug_network << "Connecting: " << d_data->info.SocketAddress().Host(true) << ":" << d_data->info.SocketAddress().Port(true) << endl;
	}

	return ::connect(Fd(), d_data->info.SocketAddress(), d_data->info.SocketAddress().Length()) == 0;
}

ssize_t
Socket::Data::Read(char *buffer, ssize_t len)
{
	if (readFunc)
	{
		return (this->*readFunc)(buffer, len);
	}
	else
	{
		return -1;
	}
}

ssize_t
Socket::Data::Write(char const *buffer, ssize_t len)
{
	if (writeFunc)
	{
		return (this->*writeFunc)(buffer, len);
	}
	else
	{
		return -1;
	}
}

ssize_t
Socket::Data::WriteDgram(char const *buffer, ssize_t len)
{
	if (Debug::Enabled(Debug::Domain::Network))
	{
		debug_network << "Writing datagram style: " << address.Host(true) << ":" << address.Port(true) << endl;
	}

	return ::sendto(fd, buffer, len, 0, address, address.Length());
}

ssize_t
Socket::Data::WriteStream(char const *buffer, ssize_t len)
{
	debug_network << "Writing stream style (" << len << ")" << endl;
	return ::send(fd, buffer, len, SEND_FLAGS);
}

bool
Socket::Listen(size_t queue)
{
	if (!*this)
	{
		return false;
	}

	return ::listen(Fd(), queue) == 0;
}

ssize_t
Socket::Data::ReadDgram(char *buffer, ssize_t len)
{
	struct sockaddr_storage addr;
	struct sockaddr *add = reinterpret_cast<struct sockaddr *>(&addr);
	ssize_t ret;

	socklen_t addrlen = sizeof(addr);

	ret = ::recvfrom(fd, buffer, len, 0, add, &addrlen);

	if (ret >= 0)
	{
		address = SocketAddress(add, addrlen);

		if (Debug::Enabled(Debug::Domain::Network))
		{
			debug_network << "Received datagram style (" << ret << "): " << address.Host() << ":" << address.Port() << endl;
		}
	}

	return ret;
}

ssize_t
Socket::Data::ReadStream(char *buffer, ssize_t len)
{
	ssize_t ret = ::recv(fd, buffer, len, 0);

	if (ret > 0 && Debug::Enabled(Debug::Domain::Network))
	{
		debug_network << "Received stream style (" << ret << "): " << address.Host() << ":" << address.Port() << endl;
	}

	return ret;
}

void
Socket::SetData(Data *data)
{
	d_data = data;
	FileDescriptor::SetData(data);
}

void
Socket::SetInfo(AddressInfo &info)
{
	d_data->info = info;

	if (info)
	{
		d_data->address = info.SocketAddress();

		Assign(::socket(info.Family(), info.SocketType(), info.Protocol()));
		Attach();

		if (info.SocketType() == SOCK_DGRAM)
		{
			d_data->writeFunc = &Data::WriteDgram;
			d_data->readFunc = &Data::ReadDgram;
		}
		else
		{
			d_data->writeFunc = &Data::WriteStream;
			d_data->readFunc = &Data::ReadStream;
		}
	}
	else
	{
		Assign(-1);
	}
}

bool
Socket::SetOption(Options::Values option)
{
	if (!*this)
	{
		return false;
	}

	int one = 1;
	return setsockopt(Fd(), SOL_SOCKET, option, &one, sizeof(one)) == 0;
}

Socket::Socket(int socket, struct sockaddr *address, socklen_t size)
:
	FileDescriptor(false)
{
	d_data = new Data();
	AddPrivateData(d_data);

	SetData(d_data);

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

	d_data->writeFunc = &Data::WriteStream;
	d_data->readFunc = &Data::ReadStream;

	Assign(socket);
	Attach();
}

Socket::Socket(AddressInfo info)
:
	FileDescriptor(false)
{
	d_data = new Data();
	AddPrivateData(d_data);

	d_data->writeFunc = 0;
	d_data->readFunc = 0;

	SetData(d_data);
	SetInfo(info);
}

Socket::Socket(bool createData)
:
	FileDescriptor(createData)
{
	d_data = 0;

	if (!createData)
		return;

	d_data = new Data();
	AddPrivateData(d_data);

	d_data->writeFunc = 0;
}
