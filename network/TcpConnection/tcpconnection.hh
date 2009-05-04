#ifndef __NETWORK_TCP_CONNECTION_H__
#define __NETWORK_TCP_CONNECTION_H__

#include "Object/object.hh"
#include "Socket/socket.hh"
#include "FileDescriptor/filedescriptor.hh"
#include <string>

namespace network
{
	class TcpConnection : public os::FileDescriptor
	{
		public:
			TcpConnection();
			TcpConnection(Socket &socket, struct sockaddr_in const &address);
			
			operator bool() const;
			
			Socket &socket();
			
			/* Signals */
		private:
			struct Data : public os::FileDescriptor::Data
			{
				Socket socket;
				struct sockaddr_in address;
			
				Data();
				Data(Socket &socket, struct sockaddr_in const &address);

				bool onSocketClosed();
				virtual void close();
			};
		
			Data *d_data;
	};
	
	inline TcpConnection::operator bool() const
	{
		return d_data->socket;
	}
	
	inline Socket &TcpConnection::socket()
	{
		return d_data->socket;
	}
}

#endif /* __NETWORK_TCP_CONNECTION_H__ */

