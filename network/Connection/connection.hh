#ifndef __NETWORK_TCP_CONNECTION_H__
#define __NETWORK_TCP_CONNECTION_H__

#include "Object/object.hh"
#include "Socket/socket.hh"
#include "FileDescriptor/filedescriptor.hh"
#include <string>

namespace network
{
	class Connection : virtual public os::FileDescriptor
	{
		public:
			Connection();
			Connection(Socket &socket);
			
			operator bool() const;
			Socket &socket();
		protected:
			struct Data : public os::FileDescriptor::Data
			{
				Socket socket;

				bool onSocketClosed();
				virtual void close();
			};

			void setSocket(Socket &socket);

			Connection(bool createData);
			void setData(Data *data);
		private:
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

