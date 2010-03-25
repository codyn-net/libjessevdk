#ifndef __JESSEVDK_NETWORK_TCP_SERVER_HH__
#define __JESSEVDK_NETWORK_TCP_SERVER_HH__

#include <jessevdk/network/server.hh>
#include <glibmm.h>
#include <string>
#include <vector>

namespace jessevdk
{
namespace network
{
	class TcpServer : public Server
	{
		public:
			struct Data : public Server::Data
			{
				std::string host;
				std::string port;

				virtual Client Accept();
			};

			TcpServer(Data *data = 0);

			TcpServer(size_t port);
			TcpServer(std::string const &port);
			TcpServer(std::string const &host, size_t port);
			TcpServer(std::string const &host, std::string const &port);

			void Set(std::string const &host, std::string const &port);
			void Set(std::string const &host, size_t port);

			void Set(std::string const &port);
			void Set(size_t port);

			virtual std::string Connection();
			virtual void SetData(Data *data);
		protected:
			virtual AddressInfo ListenAddressInfo();
			virtual bool ListenOnSocket(Socket &socket);
		private:
			Data *d_data;

			void Initialize(std::string const &host, std::string const &port);
	};
}
}

#endif /* __JESSEVDK_NETWORK_TCP_SERVER_HH__ */

// vi:ts=4
