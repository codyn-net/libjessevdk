#include "udpserver.ih"

UdpServer::Socket::Socket(int fd)
:
	network::Socket(fd)
{
}
