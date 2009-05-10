#ifndef __NETWORK_CLIENT_H__
#define __NETWORK_CLIENT_H__

#include <network/AddressInfo/addressinfo.hh>
#include <network/Socket/socket.hh>

#include <string>

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

			Client(int fd = -1);
			Client(int fd, struct sockaddr *address, socklen_t size);
		private:
			/* Private functions */
			Client(AddressInfo &info);
			static Client resolve(AddressInfo info);
	};
}

#endif /* __NETWORK_CLIENT_H__ */
