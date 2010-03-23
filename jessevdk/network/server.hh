#ifndef __JESSEVDK_NETWORK_SERVER_HH__
#define __JESSEVDK_NETWORK_SERVER_HH__

#include <jessevdk/base/object.hh>
#include <jessevdk/network/socket.hh>
#include <jessevdk/network/client.hh>

#include <glibmm.h>
#include <string>
#include <vector>

namespace jessevdk
{
namespace network
{
	class Server : virtual public base::Object
	{
		public:
			virtual bool Listen();
			void Close();

			virtual std::string Connection() = 0;

			operator bool() const;
			base::signals::Signal<Client> &OnNewConnection();
		protected:
			struct Data : virtual public base::Object::PrivateData
			{
				friend class Server;

				base::Cloneable<Socket> listenSocket;

				std::vector<Client> connections;
				base::signals::Signal<Client> onNewConnection;

				bool OnAccept(Glib::IOCondition condition);
				void OnConnectionClosed(int fd);

				~Data();

				protected:
					virtual Client Accept() = 0;
				private:
					void OnListenClosed(int fd);
			};

			Server();
			virtual void SetData(Data *data);

			virtual AddressInfo ListenAddressInfo() = 0;
			virtual bool ListenOnSocket(Socket &socket) = 0;

			virtual void InstallIOHandler();
			virtual void InstallClosedHandler();
			virtual base::Cloneable<Socket> SocketFromInfo(AddressInfo &info);

			Socket &ListenSocket();
		private:
			Data *d_data;
	};

	inline Server::operator bool() const
	{
		return d_data->listenSocket;
	}

	inline base::signals::Signal<Client> &Server::OnNewConnection()
	{
		return d_data->onNewConnection;
	}

	inline Socket &Server::ListenSocket()
	{
		return d_data->listenSocket;
	}
}
}

#endif /* __JESSEVDK_NETWORK_SERVER_HH__ */

// vi:ts=4
