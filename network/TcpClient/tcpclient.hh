#ifndef __NETWORK_TCP_CLIENT_H__
#define __NETWORK_TCP_CLIENT_H__

#include <string>
#include "Connection/tcpconnection.hh"

namespace network
{
	class TcpClient
	{
		public:
			static Connection connect(std::string const &host, std::string const &port);
			static Connection connect(std::string const &host, size_t port);
	};
}

#endif /* __NETWORK_TCP_CLIENT_H__ */

