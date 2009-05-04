#ifndef __NETWORK_TCP_SERVER_HH__
#define __NETWORK_TCP_SERVER_HH__

#include "Object/object.hh"
#include "Socket/socket.hh"
#include "Connection/connection.hh"

#include <glibmm.h>
#include <string>
#include <vector>

namespace network
{
	class TcpServer : public base::Object
	{
		struct Data : public base::Object::PrivateData
		{
			Socket listenSocket;
			Glib::RefPtr<Glib::IOSource> listenSource;
			
			std::string host;
			std::string port;
			std::vector<Connection> connections;
			
			base::signals::Signal<Connection &> onNewConnection;
			
			~Data();
			void close();
		};
		
		Data *d_data;

		public:
			TcpServer(size_t port);
			TcpServer(std::string const &port);
			TcpServer(std::string const &host, size_t port);
			TcpServer(std::string const &host, std::string const &port);
			
			bool listen();
			void close();

			base::signals::Signal<Connection &> &onNewConnection();
		private:
			void initialize(std::string const &host, std::string const &port);
			bool onAccept(Glib::IOCondition condition);
			
			bool onConnectionClosed(int fd);
	};
	
	inline base::signals::Signal<Connection &> &TcpServer::onNewConnection()
	{
		return d_data->onNewConnection;
	}
}

#endif /* __NETWORK_TCP_SERVER_HH__ */

// vi:ts=4
