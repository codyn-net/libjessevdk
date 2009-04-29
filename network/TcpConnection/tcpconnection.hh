#ifndef __OPTIMIZATION_NETWORK_TCP_CONNECTION_H__
#define __OPTIMIZATION_NETWORK_TCP_CONNECTION_H__

#include "Object/object.hh"
#include "Socket/socket.hh"
#include <glibmm.h>
#include <giomm/unixinputstream.h>
#include <string>

namespace optimization
{
namespace network
{
	class TcpConnection : public base::Object
	{
		struct Data : public base::Object::PrivateData
		{
			Glib::RefPtr<Glib::IOSource> source;
			Glib::RefPtr<Gio::UnixInputStream> stream;

			Socket socket;
			struct sockaddr_in address;
			
			base::signals::Signal<> onClosed;
			base::signals::Signal<std::string const &> onData;
			base::signals::Signal<std::string const &> onLine;
			
			std::string buffer;
			
			Data();
			Data(Socket &socket, struct sockaddr_in const &address);

			bool onSocketClosed();
			bool onIO(Glib::IOCondition condition);
		};
		
		Data *d_data;
		
		public:
			TcpConnection();
			TcpConnection(Socket &socket, struct sockaddr_in const &address);
			
			void write(std::string const &data);
			void writeLine(std::string const &data);
			
			operator bool() const;
			
			/* Signals */
			base::signals::Signal<> &onClosed();
			base::signals::Signal<std::string const &> &onData();
			base::signals::Signal<std::string const &> &onLine();
	};
	
	inline base::signals::Signal<> &TcpConnection::onClosed()
	{
		return d_data->onClosed;
	}
	
	inline base::signals::Signal<std::string const &> &TcpConnection::onData()
	{
		return d_data->onData;
	}
	
	inline base::signals::Signal<std::string const &> &TcpConnection::onLine()
	{
		return d_data->onLine;
	}
	
	inline TcpConnection::operator bool() const
	{
		return d_data->socket;
	}
}
}

#endif /* __OPTIMIZATION_NETWORK_TCP_CONNECTION_H__ */

