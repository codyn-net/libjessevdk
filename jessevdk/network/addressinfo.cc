#include "addressinfo.hh"

#include <jessevdk/os/filesystem.hh>
#include <sstream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <jessevdk/base/string.hh>

using namespace jessevdk::network;
using namespace jessevdk::base;
using namespace std;
using namespace jessevdk::os;

AddressInfo::AddressInfo()
{
	d_data = new Data();
	AddPrivateData(d_data);

	d_data->address = 0;
	d_data->current = 0;
	d_data->freeAddress = false;
}

AddressInfo::AddressInfo(int ret, struct addrinfo *addr)
{
	d_data = new Data();
	AddPrivateData(d_data);

	d_data->freeAddress = false;

	if (ret != 0 || !addr)
	{
		d_data->address = 0;
		d_data->current = 0;
	}
	else
	{
		d_data->address = addr;
		d_data->current = addr;
	}
}

AddressInfo::Data::~Data()
{
	if (address)
	{
		if (freeAddress)
		{
			delete address->ai_addr;
		}

		freeaddrinfo(address);
	}
}

addrinfo
AddressInfo::Hint(int socktype, int protocol, int flags)
{
	struct addrinfo hint;

	memset(&hint, 0, sizeof(hint));

	hint.ai_flags = flags;
	hint.ai_family = AF_UNSPEC;
	hint.ai_socktype = socktype;
	hint.ai_protocol = protocol;

	return hint;
}

bool
AddressInfo::IsIPAddress(string const &host)
{
	return String(host).Split(".").size() == 4;
}

bool
AddressInfo::IsMulticast(string const &host)
{
	size_t pos = host.find(".");

	if (pos == string::npos)
		return false;

	stringstream s;
	s << host.substr(0, pos);
	size_t part = 0;

	s >> part;

	return (part >= 224 && part <= 239);
}

bool
AddressInfo::Next()
{
	if (!d_data->current || !d_data->current->ai_next)
		return false;

	d_data->current = d_data->current->ai_next;
	return true;
}

AddressInfo
AddressInfo::Parse(string const &connection)
{
	string protocol;
	string host = "";
	string port = "";

	Split(connection, protocol, host, port);

	if (host == "" && port == "")
		return AddressInfo();

	if (protocol == "unix")
	{
		return AddressInfo::Unix(port != "" ? port : host);
	}
	else if (protocol == "tcp")
	{
		return AddressInfo::Tcp(host, port);
	}
	else if (protocol == "udp")
	{
		return AddressInfo::Udp(host, port);
	}
	else if (protocol == "multicast")
	{
		return AddressInfo::Udp(host, port);
	}

	return AddressInfo();
}

AddressInfo
AddressInfo::Resolve(std::string const &host, std::string const &port, struct addrinfo hint)
{
	struct addrinfo *addr;

	if (host == "")
		hint.ai_flags |= AI_PASSIVE;

	int ret = getaddrinfo(host == "" ? 0 : host.c_str(), port.c_str(), &hint, &addr);
	return AddressInfo(ret, addr);
}

void
AddressInfo::Split(string const &connection, string &protocol, string &host, string &port)
{
	size_t pos = connection.find("://");
	String rest;

	if (pos != string::npos)
	{
		protocol = connection.substr(0, pos);
		rest = connection.substr(pos + 3);
	}
	else
	{
		protocol = "tcp";
		rest = connection;
	}

	vector<string> parts;

	if (rest.StartsWith("::ffff:"))
	{
		parts = String(rest.substr(7)).Split(":");
		parts[0] = string("::ffff:") + parts[0];
	}
	else
	{
		parts = rest.Split(":");
	}

	if (parts.size() == 1)
	{
		if (!rest.empty() && rest.at(0) == ':')
			port = parts[0];
		else
			host = parts[0];
	}
	else
	{
		host = parts[0];
		port = parts[1];
	}
}

AddressInfo
AddressInfo::Tcp(string const &host, string const &port)
{
	return Resolve(host, port, Hint(SOCK_STREAM, IPPROTO_TCP));
}

AddressInfo
AddressInfo::Tcp(string const &port)
{
	return Tcp("", port);
}

AddressInfo
AddressInfo::Udp(string const &host, string const &port)
{
	return Resolve(host, port, Hint(SOCK_DGRAM, IPPROTO_UDP));
}

AddressInfo
AddressInfo::Udp(string const &port)
{
	return Udp("", port);
}

AddressInfo
AddressInfo::Unix(string const &filename)
{
	if (!FileSystem::DirectoryExists(FileSystem::Dirname(filename)))
	{
		return AddressInfo(-1, 0);
	}

	struct sockaddr_un *addr = new sockaddr_un();

	addr->sun_family = AF_UNIX;
	strncpy(addr->sun_path, filename.c_str(), 107);
	addr->sun_path[107] = '\0';

	struct addrinfo *info = static_cast<addrinfo *>(calloc(1, sizeof(addrinfo)));

	info->ai_family = AF_UNIX;
	info->ai_socktype = SOCK_STREAM;
	info->ai_addrlen = sizeof(struct sockaddr_un);
	info->ai_addr = (sockaddr *)addr;

	AddressInfo ret(0, info);
	ret.d_data->freeAddress = true;

	return ret;
}
