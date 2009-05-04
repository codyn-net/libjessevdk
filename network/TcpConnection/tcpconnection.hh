#ifndef __NETWORK_TCP_CONNECTION_H__
#define __NETWORK_TCP_CONNECTION_H__

#include "Object/object.hh"
#include "Socket/socket.hh"
#include <glibmm.h>
#include <giomm/unixinputstream.h>
#include <string>

namespace network
{
	class TcpConnection : public Object
	{
		struct Data : public Object::PrivateData
		{
			Glib::RefPtr<Glib::IOSource> source;
			Glib::RefPtr<Gio::UnixInputStream> stream;

			Socket socket;
			struct sockaddr_in address;
			
			signals::Signal<> onClosed;
			signals::Signal<std::string const &> onData;
			signals::Signal<std::string const &> onLine;
			
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
			signals::Signal<> &onClosed();
			signals::Signal<std::string const &> &onData();
			signals::Signal<std::string const &> &onLine();
	};
	
	inline signals::Signal<> &TcpConnection::onClosed()
	{
		return d_data->onClosed;
	}
	
	inline signals::Signal<std::string const &> &TcpConnection::onData()
	{
		return d_data->onData;
	}
	
	inline signals::Signal<std::string const &> &TcpConnection::onLine()
	{
		return d_data->onLine;
	}
	
	inline TcpConnection::operator bool() const
	{
		return d_data->socket;
	}
}

#endif /* __NETWORK_TCP_CONNECTION_H__ */

