#include "client.hh"
#include <string.h>
#include <errno.h>

#include <jessevdk/base/debug.hh>

using namespace std;
using namespace jessevdk::network;
using namespace jessevdk::base;

Client::Client(AddressInfo info)
:
	Socket(info)
{
}

Client::Client(int fd)
:
	Socket(fd)
{
}

Client::Client(int fd, struct sockaddr *address, socklen_t size)
:
	Socket(fd, address, size)
{
}

Client::Client(bool createData)
:
	Socket(createData)
{
}

Client Client::Multicast(string const &host, string const &port, size_t ttl)
{
	Client ret = Resolve<Client>(AddressInfo::Udp(host, port));

	if (ret)
	{
		char val = static_cast<char>(ttl);

		setsockopt(ret, IPPROTO_IP, IP_MULTICAST_TTL, &val, sizeof(val));
	}

	return ret;
}

Client Client::Multicast(string const &host, size_t port, size_t ttl)
{
	stringstream s;

	s << port;

	return Multicast(host, s.str(), ttl);
}

Client Client::Tcp(string const &host, string const &port)
{
	return Resolve<Client>(AddressInfo::Tcp(host, port));
}

Client Client::Tcp(string const &host, size_t port)
{
	stringstream istr;

	istr << port;
	return Tcp(host, istr.str());
}

Client Client::Udp(string const &host, string const &port)
{
	Client cl = Resolve<Client>(AddressInfo::Udp(host, port));
	cl.Detach();

	return cl;
}

Client Client::Udp(string const &host, size_t port)
{
	stringstream istr;

	istr << port;
	return Udp(host, istr.str());
}

Client Client::Unix(string const &filename)
{
	return Resolve<Client>(AddressInfo::Unix(filename));
}
