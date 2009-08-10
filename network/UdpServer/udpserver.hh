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
			
			// Relay signals from the socket
			base::signals::Signal<Glib::IOCondition> &onIO();
			base::signals::Signal<int> &onClosed();
			base::signals::Signal<os::FileDescriptor::DataArgs> &onData();
		protected:
			virtual AddressInfo listenAddressInfo();
			virtual bool listenOnSocket(network::Socket &socket);
			virtual base::Cloneable<Socket> socketFromInfo(AddressInfo &info);
			
			virtual void installIOHandler();
		private:
			class Socket : public network::Socket
			{
				struct Data : public network::Socket::Data
				{
					protected:
						virtual base::Cloneable<FileDescriptor::DataArgs> createArgs(int fd, std::string *buffer);
				};

				Data *d_data;

				public:
					Socket(AddressInfo &info);
					Socket(int fd = -1);
					
					Socket *clone() const;
			};
			
			void initialize(std::string const &host, std::string const &port);
			void setupBroadcast(network::Socket &socket);
			void setupMulticast(network::Socket &socket);
			
			struct Data : public Server::Data
			{
				std::string host;
				std::string port;
				
				bool broadcast;
				Socket socket;

				protected:
					virtual Client accept();
			};
		
			Data *d_data;
	};
}

#endif /* __NETWORK_UDP_SERVER_HH__ */

// vi:ts=4
