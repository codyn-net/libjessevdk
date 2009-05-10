#ifndef __NETWORK_SOCKET_ADDRESS_H__
#define __NETWORK_SOCKET_ADDRESS_H__

#include <base/Object/object.hh>
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
			int family() const;

			std::string const &port(bool numeric = false) const;
			std::string const &host(bool numeric = false) const;
			
			operator sockaddr const *() const;
			size_t length() const;
		private:
			/* Private functions */
		
	};
	
	inline int SocketAddress::family() const
	{
		return d_data->address ? d_data->address->sa_family : 0;
	}
	
	inline SocketAddress::operator sockaddr const *() const
	{
		return d_data->address;
	}
	
	inline size_t SocketAddress::length() const
	{
		return d_data->size;
	}
}

#endif /* __NETWORK_SOCKET_ADDRESS_H__ */
