#ifndef __NETWORK_SERVER_HH__
#define __NETWORK_SERVER_HH__

#include "Object/object.hh"
#include "Socket/socket.hh"
#include "Connection/connection.hh"

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

			base::signals::Signal<Connection &> &onNewConnection();
		protected:
			struct Data : virtual public base::Object::PrivateData
			{
				friend class  Server;

				Socket listenSocket;
				Glib::RefPtr<Glib::IOSource> listenSource;

				std::vector<Connection> connections;
				base::signals::Signal<Connection &> onNewConnection;
			
				~Data();
	
				bool onAccept(Glib::IOCondition condition);
				void onConnectionClosed(int fd);
				
				protected:
					virtual void close();
					virtual Socket accept() = 0;
			};

			Server();
			void setData(Data *data);

			virtual AddressInfo listenAddressInfo() = 0;
			virtual bool listenOnSocket(Socket &socket) = 0;
			
			Socket &listenSocket();
		private:
			Data *d_data;
	};
	
	inline base::signals::Signal<Connection &> &Server::onNewConnection()
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
