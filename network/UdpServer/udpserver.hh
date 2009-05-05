#ifndef __NETWORK_UDP_SERVER_HH__
#define __NETWORK_UDP_SERVER_HH__

#include "Server/server.hh"
#include <glibmm.h>
#include <string>
#include <vector>

namespace network
{
	class UdpServer : public Server
	{
		struct Data : public base::Object::PrivateData
		{
			std::string host;
			std::string port;
		};
		
		Data *d_data;

		public:
			UdpServer(size_t port);
			UdpServer(std::string const &port);
			UdpServer(std::string const &host, size_t port);
			UdpServer(std::string const &host, std::string const &port);
		
		protected:
			virtual Socket accept();
			virtual AddressInfo listenAddressInfo();
		private:
			void initialize(std::string const &host, std::string const &port);
	};
}

#endif /* __NETWORK_TCP_SERVER_HH__ */

// vi:ts=4
