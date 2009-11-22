#ifndef __JESSEVDK_NETWORK_CLIENT_H__
#define __JESSEVDK_NETWORK_CLIENT_H__

#include <jessevdk/network/addressinfo.hh>
#include <jessevdk/network/socket.hh>
#include <jessevdk/base/debug.hh>
#include <string>
#include <errno.h>
#include <cstring>

namespace jessevdk
{
namespace network
{
	class Client : public Socket
	{
		public:
			/* Constructor/destructor */
			static Client Tcp(std::string const &host, std::string const &port);
			static Client Tcp(std::string const &host, size_t port);

			static Client Unix(std::string const &filename);

			static Client Udp(std::string const &host, std::string const &port);
			static Client Udp(std::string const &host, size_t port);

			static Client Multicast(std::string const &host, std::string const &port, size_t ttl = 1);
			static Client Multicast(std::string const &host, size_t port, size_t ttl = 1);

			Client(int fd = -1);
			Client(int fd, struct sockaddr *address, socklen_t size);
			Client(AddressInfo info);

			template <typename T>
			static T Resolve(AddressInfo info);
		protected:
			Client(bool createData);
		private:
			/* Private functions */
	};

	template <typename T>
	T Client::Resolve(AddressInfo info)
	{
		if (!info)
		{
			return T();
		}

		do
		{
			T client(info);

			if (!client)
			{
				debug_network << "Could not create socket: " << strerror(errno) << std::endl;
				continue;
			}

			Socket &s = dynamic_cast<Socket &>(client);

			if (info.SocketType() == AddressInfo::SocketType::Stream && !s.Connect())
			{
				debug_network << "Could not connect: " << strerror(errno) << std::endl;
				continue;
			}

			if (base::Debug::Enabled(base::Debug::Domain::Network))
			{
				debug_network << "Connected to " << info.SocketAddress().Host(true) << ":" << info.SocketAddress().Port(true) << std::endl;
			}

			return client;
		} while (info.Next());

		return T();
	}
}
}

#endif /* __JESSEVDK_NETWORK_CLIENT_H__ */
