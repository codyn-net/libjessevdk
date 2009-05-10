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
					Reuse = SO_REUSEADDR,
					Broadcast = SO_BROADCAST,
					KeepAlive = SO_KEEPALIVE
				};
			};
			
			Socket(int socket = -1);
			Socket(AddressInfo info);
			Socket(int socket, struct sockaddr *address, socklen_t size);
			
			void setInfo(AddressInfo &info);
			
			bool bind();
			bool setOption(Options::Values option);
			bool listen(size_t queue);
			bool connect();
			
			SocketAddress &address();
		protected:
			struct Data	: virtual public os::FileDescriptor::Data
			{
				friend class Socket;

				AddressInfo info;
				SocketAddress address;
				
				ssize_t (Socket::Data::*writeFunc)(char const *buffer, ssize_t len);
				ssize_t (Socket::Data::*readFunc)(char *buffer, ssize_t len);
				
				protected:
					virtual ssize_t write(char const *buffer, ssize_t len);
					virtual ssize_t read(char *buffer, ssize_t len);
				private:
					ssize_t writeStream(char const *buffer, ssize_t len);
					ssize_t writeDgram(char const *buffer, ssize_t len);

					ssize_t readStream(char *buffer, ssize_t len);
					ssize_t readDgram(char *buffer, ssize_t len);
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

