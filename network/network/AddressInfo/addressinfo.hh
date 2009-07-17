#ifndef __NETWORK_ADDRESS_INFO_H__
#define __NETWORK_ADDRESS_INFO_H__

#include <base/Object/object.hh>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <network/SocketAddress/socketaddress.hh>

namespace network
{
	class AddressInfo : public base::Object
	{
		struct Data : public Object::PrivateData
		{
			struct addrinfo *address;
			struct addrinfo *current;
			
			bool freeAddress;
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
			
			operator bool() const;
			bool next();
			
			/* Getters */
			int family() const;
			int socketType() const;
			int protocol() const;
			
			SocketAddress socketAddress() const;
			
			static AddressInfo Unix(std::string const &filename);
			
			static AddressInfo Tcp(std::string const &host, std::string const &port);
			static AddressInfo Tcp(std::string const &port);

			static AddressInfo Udp(std::string const &host, std::string const &port);
			static AddressInfo Udp(std::string const &port);
			
			static AddressInfo Parse(std::string const &connection);
			static void Split(std::string const &connection, std::string &protocol, std::string &host, std::string &port);
			
			static bool isMulticast(std::string const &host);
			static bool isIPAddress(std::string const &addr);
		private:
			AddressInfo(int ret, struct addrinfo *addr);
			
			static addrinfo hint(int socktype, int protocol, int flags = 0);
			static AddressInfo resolve(std::string const &host, std::string const &port, struct addrinfo hint);
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

