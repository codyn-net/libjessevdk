#ifndef __OTPIMIZATION_NETWORK_ADDRESS_INFO_H__
#define __OTPIMIZATION_NETWORK_ADDRESS_INFO_H__

#include "Object/object.hh"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

namespace optimization
{
namespace network
{
	class AddressInfo : public base::Object
	{
		struct Data : public base::Object::PrivateData
		{
			struct addrinfo *address;
			struct addrinfo *current;
		};
		
		Data *d_data;
		
		public:
			AddressInfo();
			AddressInfo(int ret, struct addrinfo *addr);
			AddressInfo(std::string const &host, std::string const &port);
			AddressInfo(std::string const &host, std::string const &port, struct addrinfo hint);
			
			operator bool() const;
			bool next();
			
			/* Getters */
			int family() const;
			int socketType() const;
			int protocol() const;
			
			struct sockaddr *socketAddress() const;
			size_t socketAddressLength() const;
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
	
	inline struct sockaddr *AddressInfo::socketAddress() const
	{
		return d_data->current ? d_data->current->ai_addr : 0;
	}
	
	inline size_t AddressInfo::socketAddressLength() const
	{
		return d_data->current ? d_data->current->ai_addrlen : 0;
	}
}
}

#endif /* __OTPIMIZATION_NETWORK_ADDRESS_INFO_H__ */

