#ifndef __JESSEVDK_NETWORK_UDP_SERVER_HH__
#define __JESSEVDK_NETWORK_UDP_SERVER_HH__

#include <jessevdk/network/server.hh>
#include <glibmm.h>
#include <string>
#include <vector>

namespace jessevdk
{
namespace network
{
	class UdpServer : public Server, public Client
	{
		public:
			struct DataArgs : public FileDescriptor::DataArgs
			{
				SocketAddress Address;

				DataArgs(int fd, std::string *buffer, SocketAddress &address);
				DataArgs *Clone() const;
			};

			UdpServer(size_t port);
			UdpServer(std::string const &port);
			UdpServer(std::string const &host, size_t port);
			UdpServer(std::string const &host, std::string const &port);

			void Set(std::string const &host, std::string const &port);
			void Set(std::string const &host, size_t port);

			void Set(std::string const &port);
			void Set(size_t port);

			virtual bool Listen();
			virtual std::string Connection();

			void EnableBroadcast();

			bool IsMulticast() const;

			// Relay signals from the socket
			base::signals::Signal<Glib::IOCondition> &OnIO();
			base::signals::Signal<int> &OnClosed();
			base::signals::Signal<os::FileDescriptor::DataArgs> &OnData();
		protected:
			virtual AddressInfo ListenAddressInfo();
			virtual bool ListenOnSocket(network::Socket &socket);
			virtual base::Cloneable<Socket> SocketFromInfo(AddressInfo &info);

			virtual void InstallIOHandler();
		private:
			class Socket : public network::Socket
			{
				struct Data : public network::Socket::Data
				{
					protected:
						virtual base::Cloneable<FileDescriptor::DataArgs> CreateArgs(int fd, std::string *buffer);
				};

				Data *d_data;

				public:
					Socket(AddressInfo &info);
					Socket(int fd = -1);

					Socket *Clone() const;
			};

			void Initialize(std::string const &host, std::string const &port);
			void SetupBroadcast(network::Socket &socket);
			void SetupMulticast(network::Socket &socket);

			struct Data : public Server::Data
			{
				std::string host;
				std::string port;

				bool broadcast;
				Socket socket;

				protected:
					virtual Client Accept();
			};

			Data *d_data;
	};
}
}

#endif /* __JESSEVDK_NETWORK_UDP_SERVER_HH__ */

// vi:ts=4
