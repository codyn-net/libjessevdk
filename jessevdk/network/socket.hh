#ifndef __JESSEVDK_NETWORK_SOCKET_H__
#define __JESSEVDK_NETWORK_SOCKET_H__

#include <jessevdk/base/object.hh>
#include <jessevdk/network/addressinfo.hh>
#include <jessevdk/os/filedescriptor.hh>

namespace jessevdk
{
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

			Socket(int socket = -1, struct sockaddr *address = 0, socklen_t size = 0);
			Socket(AddressInfo info);

			Socket *Clone() const;
			void SetInfo(AddressInfo &info);

			bool Bind();
			bool SetOption(Options::Values option);
			bool Listen(size_t queue);
			bool Connect();

			SocketAddress &Address();
		protected:
			struct Data	: public os::FileDescriptor::Data
			{
				friend class Socket;

				AddressInfo info;
				SocketAddress address;

				ssize_t (Socket::Data::*writeFunc)(char const *buffer, ssize_t len);
				ssize_t (Socket::Data::*readFunc)(char *buffer, ssize_t len);

				protected:
					virtual ssize_t Write(char const *buffer, ssize_t len);
					virtual ssize_t Read(char *buffer, ssize_t len);
				private:
					ssize_t WriteStream(char const *buffer, ssize_t len);
					ssize_t WriteDgram(char const *buffer, ssize_t len);

					ssize_t ReadStream(char *buffer, ssize_t len);
					ssize_t ReadDgram(char *buffer, ssize_t len);
			};

			Socket(bool createData);
			void SetData(Data *data);
		public:
			Data *d_data;
	};

	inline SocketAddress &Socket::Address()
	{
		return d_data->address;
	}
}
}

#endif /* __JESSEVDK_NETWORK_SOCKET_H__ */

