#ifndef __JESSEVDK_NETWORK_SOCKET_ADDRESS_H__
#define __JESSEVDK_NETWORK_SOCKET_ADDRESS_H__

#include <jessevdk/base/object.hh>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>

namespace jessevdk
{
namespace network
{
	class SocketAddress : public base::Object
	{
		struct Data : public base::Object::PrivateData
		{
			struct Cached
			{
				enum Values
				{
					None = 0,
					Host = 1 << 0,
					Port = 1 << 1
				};
			};

			/* Instance data */
			struct sockaddr *address;
			socklen_t size;

			std::string host;
			std::string port;

			int cached;

			~Data();
		};

		Data *d_data;

		public:
			/* Constructor/destructor */
			SocketAddress();
			SocketAddress(struct sockaddr const *address, socklen_t size);

			/* Public functions */
			int Family() const;

			std::string const &Port(bool numeric = false) const;
			std::string const &Host(bool numeric = false) const;

			operator std::string () const;

			operator sockaddr const *() const;
			size_t Length() const;
		private:
			/* Private functions */

	};

	inline int SocketAddress::Family() const
	{
		return d_data->address ? d_data->address->sa_family : 0;
	}

	inline SocketAddress::operator sockaddr const *() const
	{
		return d_data->address;
	}

	inline SocketAddress::operator std::string () const
	{
		return Host() + ":" + Port();
	}

	inline size_t SocketAddress::Length() const
	{
		return d_data->size;
	}
}
}

#endif /* __JESSEVDK_NETWORK_SOCKET_ADDRESS_H__ */
