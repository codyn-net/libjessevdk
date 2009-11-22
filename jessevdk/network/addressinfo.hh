#ifndef __JESSEVDK_NETWORK_ADDRESS_INFO_H__
#define __JESSEVDK_NETWORK_ADDRESS_INFO_H__

#include <jessevdk/base/object.hh>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <jessevdk/network/socketaddress.hh>

namespace jessevdk
{
namespace network
{
	class AddressInfo : public base::Object
	{
		struct Data : public Object::PrivateData
		{
			struct addrinfo *address;
			struct addrinfo *current;

			bool freeAddress;
			~Data();
		};

		Data *d_data;

		public:
			struct SocketType
			{
				enum
				{
					Stream = SOCK_STREAM,
					Datagram = SOCK_DGRAM
				};
			};

			AddressInfo();

			operator bool() const;
			bool Next();

			/* Getters */
			int Family() const;
			int SocketType() const;
			int Protocol() const;

			jessevdk::network::SocketAddress SocketAddress() const;

			static AddressInfo Unix(std::string const &filename);

			static AddressInfo Tcp(std::string const &host, std::string const &port);
			static AddressInfo Tcp(std::string const &port);

			static AddressInfo Udp(std::string const &host, std::string const &port);
			static AddressInfo Udp(std::string const &port);

			static AddressInfo Parse(std::string const &connection);
			static void Split(std::string const &connection, std::string &protocol, std::string &host, std::string &port);

			static bool IsMulticast(std::string const &host);
			static bool IsIPAddress(std::string const &addr);
		private:
			AddressInfo(int ret, struct addrinfo *addr);

			static addrinfo Hint(int socktype, int protocol, int flags = 0);
			static AddressInfo Resolve(std::string const &host, std::string const &port, struct addrinfo hint);
	};

	inline AddressInfo::operator bool() const
	{
		return d_data->address != 0;
	}

	inline int AddressInfo::Family() const
	{
		return d_data->current ? d_data->current->ai_family : 0;
	}

	inline int AddressInfo::SocketType() const
	{
		return d_data->current ? d_data->current->ai_socktype : 0;
	}

	inline int AddressInfo::Protocol() const
	{
		return d_data->current ? d_data->current->ai_protocol : 0;
	}

	inline jessevdk::network::SocketAddress AddressInfo::SocketAddress() const
	{
		return d_data->current ? jessevdk::network::SocketAddress(d_data->current->ai_addr, d_data->current->ai_addrlen) : SocketAddress();
	}
}
}

#endif /* __JESSEVDK_NETWORK_ADDRESS_INFO_H__ */

