#ifndef __BASE_NETWORK_TCP_CLIENT_H__
#define __BASE_NETWORK_TCP_CLIENT_H__

#include <string>
#include "TcpConnection/tcpconnection.hh"

namespace base
{
namespace network
{
	class TcpClient
	{
		public:
			static TcpConnection connect(std::string const &host, std::string const &port);
			static TcpConnection connect(std::string const &host, size_t port);
	};
}
}

#endif /* __BASE_NETWORK_TCP_CLIENT_H__ */

