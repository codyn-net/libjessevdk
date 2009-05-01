#ifndef __BASE_NETWORK_TCP_SERVER_HH__
#define __BASE_NETWORK_TCP_SERVER_HH__

#include "Object/object.hh"
#include "Socket/socket.hh"
#include "TcpConnection/tcpconnection.hh"

#include <glibmm.h>
#include <string>
#include <vector>

namespace base
{
namespace network
{
	class TcpServer : public Object
	{
		struct Data : public Object::PrivateData
		{
			Socket listenSocket;
			Glib::RefPtr<Glib::IOSource> listenSource;
			
			std::string host;
			std::string port;
			std::vector<TcpConnection> connections;
			
			signals::Signal<TcpConnection &> onNewConnection;
			
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

			signals::Signal<TcpConnection &> &onNewConnection();
		private:
			void initialize(std::string const &host, std::string const &port);
			bool onAccept(Glib::IOCondition condition);
			
			bool onConnectionClosed(TcpConnection connection);
	};
	
	inline signals::Signal<TcpConnection &> &TcpServer::onNewConnection()
	{
		return d_data->onNewConnection;
	}
}
}

#endif /* __BASE_NETWORK_TCP_SERVER_HH__ */

// vi:ts=4
