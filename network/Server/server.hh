#ifndef __NETWORK_SERVER_HH__
#define __NETWORK_SERVER_HH__

#include "Object/object.hh"
#include "Socket/socket.hh"
#include "Client/client.hh"

#include <glibmm.h>
#include <string>
#include <vector>

namespace network
{
	class Server : virtual public base::Object
	{
		public:
			virtual bool listen();
			void close();

			base::signals::Signal<Client &> &onNewConnection();
		protected:
			struct Data : virtual public base::Object::PrivateData
			{
				friend class Server;

				Socket listenSocket;

				std::vector<Client> connections;
				base::signals::Signal<Client &> onNewConnection;

				bool onAccept(Glib::IOCondition condition);
				void onConnectionClosed(int fd);
				
				protected:
					virtual Client accept() = 0;
				
				private:
					void onListenClosed(int fd);
			};

			Server();
			void setData(Data *data);

			virtual AddressInfo listenAddressInfo() = 0;
			virtual bool listenOnSocket(Socket &socket) = 0;
			virtual void installIOHandler();
			virtual void installClosedHandler();
			virtual Socket &socketFromInfo(AddressInfo &info);
			
			Socket &listenSocket();
		private:
			Data *d_data;
	};
	
	inline base::signals::Signal<Client &> &Server::onNewConnection()
	{
		return d_data->onNewConnection;
	}
	
	inline Socket &Server::listenSocket()
	{
		return d_data->listenSocket;
	}
}

#endif /* __NETWORK_SERVER_HH__ */

// vi:ts=4
