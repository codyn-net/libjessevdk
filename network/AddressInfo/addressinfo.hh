#ifndef __NETWORK_ADDRESS_INFO_H__
#define __NETWORK_ADDRESS_INFO_H__

#include "Object/object.hh"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "SocketAddress/socketaddress.hh"

namespace network
{
	class AddressInfo : public base::Object
	{
		struct Data : public Object::PrivateData
		{
			struct addrinfo *address;
			struct addrinfo *current;
			
			~Data();
		};
		
		Data *d_data;
		
		public:
			struct SocketType
			{
				enum
				{
					Stream = SOCK_STREAM,
					Datagram = SOCK_DGRAM
				};
			};
			
			AddressInfo();
			AddressInfo(int ret, struct addrinfo *addr);
			AddressInfo(std::string const &host, std::string const &port);
			AddressInfo(std::string const &host, std::string const &port, struct addrinfo hint);
			
			AddressInfo(std::string const &filename);
			
			operator bool() const;
			bool next();
			
			/* Getters */
			int family() const;
			int socketType() const;
			int protocol() const;
			
			SocketAddress socketAddress() const;
		private:
			void resolve(std::string const &host, std::string const &port, struct addrinfo hint);
			void initialize(int ret, struct addrinfo *addr);
	};
	
	inline AddressInfo::operator bool() const
	{
		return d_data->address != 0;
	}
	
	inline int AddressInfo::family() const
	{
		return d_data->current ? d_data->current->ai_family : 0;
	}

	inline int AddressInfo::socketType() const
	{
		return d_data->current ? d_data->current->ai_socktype : 0;
	}

	inline int AddressInfo::protocol() const
	{
		return d_data->current ? d_data->current->ai_protocol : 0;
	}
	
	inline SocketAddress AddressInfo::socketAddress() const
	{
		return d_data->current ? SocketAddress(d_data->current->ai_addr, d_data->current->ai_addrlen) : SocketAddress();
	}
}

#endif /* __NETWORK_ADDRESS_INFO_H__ */

