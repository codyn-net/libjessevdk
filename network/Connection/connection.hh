#ifndef __NETWORK_TCP_CONNECTION_H__
#define __NETWORK_TCP_CONNECTION_H__

#include "Object/object.hh"
#include "Socket/socket.hh"
#include "FileDescriptor/filedescriptor.hh"
#include <string>

namespace network
{
	class Connection : public os::FileDescriptor
	{
		public:
			Connection();
			Connection(Socket &socket);
			
			operator bool() const;
			Socket &socket();
			
			std::string host() const;
			size_t port() const;
		protected:
			void setSocket(Socket &socket);
		private:
			struct Data : public os::FileDescriptor::Data
			{
				Socket socket;
				struct sockaddr_in lastAddress;

				bool onSocketClosed();
				virtual void close();
				
				virtual bool onIO(Glib::IOCondition condition);
			};
		
			Data *d_data;
	};
	
	inline Connection::operator bool() const
	{
		return d_data->socket;
	}
	
	inline Socket &Connection::socket()
	{
		return d_data->socket;
	}
}

#endif /* __NETWORK_TCP_CONNECTION_H__ */

