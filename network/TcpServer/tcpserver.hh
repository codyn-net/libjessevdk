#ifndef __OPTIMIZATION_NETWORK_TCP_SERVER_HH__
#define __OPTIMIZATION_NETWORK_TCP_SERVER_HH__

#include "Object/object.hh"
#include "Socket/socket.hh"
#include "TcpConnection/tcpconnection.hh"

#include <glibmm.h>
#include <string>
#include <vector>

namespace optimization
{
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
			std::vector<TcpConnection> connections;
			
			base::signals::Signal<TcpConnection &> onNewConnection;
			
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

			base::signals::Signal<TcpConnection &> &onNewConnection();
		private:
			void initialize(std::string const &host, std::string const &port);
			bool onAccept(Glib::IOCondition condition);
			
			bool onConnectionClosed(TcpConnection connection);
	};
	
	inline base::signals::Signal<TcpConnection &> &TcpServer::onNewConnection()
	{
		return d_data->onNewConnection;
	}
}
}

#endif /* __OPTIMIZATION_NETWORK_TCP_SERVER_HH__ */

// vi:ts=4
