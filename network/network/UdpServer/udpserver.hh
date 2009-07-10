#ifndef __NETWORK_UDP_SERVER_HH__
#define __NETWORK_UDP_SERVER_HH__

#include <network/Server/server.hh>
#include <glibmm.h>
#include <string>
#include <vector>

namespace network
{
	class UdpServer : public Server, public Client
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

			void set(std::string const &host, std::string const &port);
			void set(std::string const &host, size_t port);

			void set(std::string const &port);
			void set(size_t port);

			virtual bool listen();
			virtual std::string connection();

			void enableBroadcast();
			
			bool isMulticast() const;
		protected:
			virtual AddressInfo listenAddressInfo();
			virtual bool listenOnSocket(Socket &socket);
			virtual Socket &socketFromInfo(AddressInfo &info);
			
			virtual void installIOHandler();
		private:
			void initialize(std::string const &host, std::string const &port);
			void setupBroadcast(Socket &socket);
			void setupMulticast(Socket &socket);
			
			struct Data : public Server::Data, public Socket::Data
			{
				std::string host;
				std::string port;
				
				bool broadcast;

				protected:
					virtual base::Cloneable<FileDescriptor::DataArgs> createArgs(int fd, std::string *buffer);
					virtual Client accept();
			};
		
			Data *d_data;
	};
}

#endif /* __NETWORK_TCP_SERVER_HH__ */

// vi:ts=4
