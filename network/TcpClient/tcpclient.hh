#ifndef __NETWORK_TCP_CLIENT_H__
#define __NETWORK_TCP_CLIENT_H__

#include <string>
#include "Client/client.hh"

namespace network
{
	class TcpClient : public Client
	{
		struct Data : public base::Object::PrivateData
		{
			std::string host;
			std::string port;
		};
		
		Data *d_data;
		
		public:
			TcpClient();
			TcpClient(std::string const &host, std::string const &port);
			TcpClient(std::string const &host, size_t port);
		protected:
			AddressInfo connectAddressInfo();
		private:
			void initialize(std::string const &host, std::string const &port);
	};
}

#endif /* __NETWORK_TCP_CLIENT_H__ */

