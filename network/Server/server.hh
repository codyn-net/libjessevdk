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
		struct Data : public base::Object::PrivateData
		{
			Socket listenSocket;
			Glib::RefPtr<Glib::IOSource> listenSource;

			std::vector<Connection> connections;
			base::signals::Signal<Connection &> onNewConnection;
			
			~Data();
			void close();
		};
		
		Data *d_data;

		public:
			Server();
			
			virtual bool listen();
			virtual void close();

			base::signals::Signal<Connection &> &onNewConnection();
		protected:
			virtual Socket accept() = 0;
			virtual AddressInfo listenAddressInfo() = 0;
			virtual bool listenOnSocket(Socket &socket) = 0;
			
			Socket &listenSocket();
		private:
			void initialize();
			bool onAccept(Glib::IOCondition condition);
			
			bool onConnectionClosed(int fd);
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
