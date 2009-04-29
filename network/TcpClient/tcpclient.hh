#ifndef __OPTIMIZATION_NETWORK_TCP_CLIENT_H__
#define __OPTIMIZATION_NETWORK_TCP_CLIENT_H__

#include <string>
#include "TcpConnection/tcpconnection.hh"

namespace optimization
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

#endif /* __OPTIMIZATION_NETWORK_TCP_CLIENT_H__ */

