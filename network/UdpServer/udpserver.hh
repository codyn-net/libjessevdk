#ifndef __NETWORK_UDP_SERVER_HH__
#define __NETWORK_UDP_SERVER_HH__

#include "Server/server.hh"
#include <glibmm.h>
#include <string>
#include <vector>

namespace network
{
	class UdpServer : public Server, public Connection
	{
		public:
			struct DataArgs : public FileDescriptor::DataArgs
			{
				SocketAddress address;

				DataArgs(int fd, std::string *buffer, SocketAddress &address);
				DataArgs *clone() const;
			};

			UdpServer(size_t port);
			UdpServer(std::string const &port);
			UdpServer(std::string const &host, size_t port);
			UdpServer(std::string const &host, std::string const &port);
		
			virtual bool listen();
		protected:
			virtual Socket accept();
			virtual AddressInfo listenAddressInfo();
			virtual bool listenOnSocket(Socket &socket);
		private:
			void initialize(std::string const &host, std::string const &port);

			struct Data : public Connection::Data
			{
				std::string host;
				std::string port;
				
				SocketAddress address;

				protected:
					virtual int recv(std::string &data);
					virtual base::Cloneable<FileDescriptor::DataArgs> createArgs(int fd, std::string *buffer);
			};
		
			Data *d_data;
	};
}

#endif /* __NETWORK_TCP_SERVER_HH__ */

// vi:ts=4
