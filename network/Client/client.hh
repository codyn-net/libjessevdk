#ifndef __NETWORK_CLIENT_H__
#define __NETWORK_CLIENT_H__

#include <network/AddressInfo/addressinfo.hh>
#include <network/Socket/socket.hh>
#include <base/Debug/debug.hh>
#include <string>
#include <errno.h>
#include <cstring>

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
			static T resolve(AddressInfo info);
		protected:
			Client(bool createData);
		private:
			/* Private functions */
	};
	
	template <typename T>
	T Client::resolve(AddressInfo info)
	{
		if (!info)
			return T();
	
		do
		{
			T client(info);
		
			if (!client)
			{
				debug_network << "Could not create socket: " << strerror(errno) << std::endl;
				continue;
			}

			Socket &s = dynamic_cast<Socket &>(client);
		
			if (info.socketType() == AddressInfo::SocketType::Stream && !s.connect())
			{
				debug_network << "Could not connect: " << strerror(errno) << std::endl;
				continue;
			}
		
			if (base::Debug::enabled(base::Debug::Domain::Network))
			{
				debug_network << "Connected to " << info.socketAddress().host(true) << ":" << info.socketAddress().port(true) << std::endl;
			}

			return client;
		} while (info.next());
	
		return T();
	}
}

#endif /* __NETWORK_CLIENT_H__ */
