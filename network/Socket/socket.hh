#ifndef __NETWORK_SOCKET_H__
#define __NETWORK_SOCKET_H__

#include "Object/object.hh"
#include "AddressInfo/addressinfo.hh"
#include "FileDescriptor/filedescriptor.hh"

namespace network
{
	class Socket : public os::FileDescriptor
	{
		public:
			struct Options
			{
				enum Values
				{
					Reuse = SO_REUSEADDR
				};
			};
			
			Socket(int socket = -1);
			Socket(AddressInfo info);
			Socket(int socket, struct sockaddr *address, socklen_t size);
			
			bool bind();
			bool setOption(Options::Values option);
			bool listen(size_t queue);
			bool connect();
			
			SocketAddress &address();
		protected:
			struct Data	: virtual public os::FileDescriptor::Data
			{
				AddressInfo info;
				SocketAddress address;
			};

			Socket(bool createData);
			void setData(Data *data);
		private:
			Data *d_data;
	};
	
	inline SocketAddress &Socket::address()
	{
		return d_data->address;
	}
}

#endif /* __NETWORK_SOCKET_H__ */

