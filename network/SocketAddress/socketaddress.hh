#ifndef __NETWORK_SOCKET_ADDRESS_H__
#define __NETWORK_SOCKET_ADDRESS_H__

#include "Object/object.hh"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>

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
			struct sockaddr_in address;
			
			std::string host;
			std::string port;
			
			int cached;
		};

		Data *d_data;

		public:
			/* Constructor/destructor */
			SocketAddress();
			SocketAddress(struct sockaddr_in const &address);
		
			/* Public functions */
			int family() const;

			std::string const &port() const;
			std::string const &host() const;
			
			operator sockaddr const *() const;
			size_t length() const;
		private:
			/* Private functions */
		
	};
	
	inline int SocketAddress::family() const
	{
		return d_data->address.sin_family;
	}
	
	inline SocketAddress::operator sockaddr const *() const
	{
		return reinterpret_cast<sockaddr *>(&d_data->address);
	}
	
	inline size_t SocketAddress::length() const
	{
		return sizeof(sockaddr_in);
	}
}

#endif /* __NETWORK_SOCKET_ADDRESS_H__ */
