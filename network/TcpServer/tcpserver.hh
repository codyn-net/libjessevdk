#ifndef __NETWORK_TCP_SERVER_HH__
#define __NETWORK_TCP_SERVER_HH__

#include <network/Server/server.hh>
#include <glibmm.h>
#include <string>
#include <vector>

namespace network
{
	class TcpServer : public Server
	{
		struct Data : public Server::Data
		{
			std::string host;
			std::string port;
			
			virtual Client accept();
		};
		
		Data *d_data;

		public:
			TcpServer(size_t port);
			TcpServer(std::string const &port);
			TcpServer(std::string const &host, size_t port);
			TcpServer(std::string const &host, std::string const &port);
		
		protected:
			virtual AddressInfo listenAddressInfo();
			virtual bool listenOnSocket(Socket &socket);
		private:
			void initialize(std::string const &host, std::string const &port);
	};
}

#endif /* __NETWORK_TCP_SERVER_HH__ */

// vi:ts=4
